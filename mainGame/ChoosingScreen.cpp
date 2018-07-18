//
// Created by Ackan on 14.06.2018.
//

#include "ChoosingScreen.h"
#include "choosingScreenInitLoad.inl"
#include "gameConstants.h"

const sf::Time ChoosingScreen::TimePerFrame = sf::seconds(1.f/60.f);



ChoosingScreen::ChoosingScreen(sf::RenderWindow* _winPtr, int _width, int _height)
: gameWindowPtr( _winPtr ),
  width( _width ),
  height( _height ),
  chooseScreenDeltaY(130),
  amountOfChosenUnitsToDisplay(0),
  maxOfChosenUnitsToDisplay(18),
  chosenRace(NOD),
  choosingScreenRunning( true )
  //allNodUnitsDB()
{
    initLoad();

}
// TODO SWITCH BETWEEN ARMIES FOR BOTH PLAYERS
void changeChosenRaceTo( RACES _race )
{
    if( _race == RACES::NOD )
    {
        for( int i=0; i<amountOfNodUnits; ++i )
        {

        }
    }
}

void ChoosingScreen::processEvents()
{
    sf::Event event;
    while (gameWindowPtr->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::MouseWheelMoved:
                handleInputMouseScroll( event.mouseWheel.delta );
                break;

            case sf::Event::Closed:
                gameWindowPtr->close();
                break;

            case sf::Event::MouseButtonReleased:
                handleInputMouse( event.mouseButton.button );
                break;

            case sf::Event::KeyReleased:
                handleInputKeyboard( event.key.code );
                break;
        }
    }
}

void ChoosingScreen::handleInputMouseScroll( float _delta )
{

    // scrolling up
        if (_delta < 0 ) {
            if( chooseScreenDeltaY + 10 < 300 ) {
                chooseScreenDeltaY += 10;
                unitsToChooseFromS.setTextureRect(sf::IntRect(0,
                                                              chooseScreenDeltaY,
                                                              (int) backOfUToChooseSizeX,
                                                              backOfUToChooseSizeY));
            }
        }
        // scrolling down
        if (_delta > 0  ) {
            if( chooseScreenDeltaY - 10 > 120 ) {
                chooseScreenDeltaY -= 10;
                unitsToChooseFromS.setTextureRect(sf::IntRect(0,
                                                              chooseScreenDeltaY,
                                                              (int) backOfUToChooseSizeX,
                                                              backOfUToChooseSizeY));
            }
        }
}

void ChoosingScreen::handleInputMouse( sf::Mouse::Button _released )
{
    sf::Vector2f mousePos = sf::Vector2f( static_cast<float>(sf::Mouse::getPosition(*gameWindowPtr).x), static_cast<float>(sf::Mouse::getPosition(*gameWindowPtr).y) );
    std::cout << "RMB clicket at x: " << mousePos.x << " y: " << mousePos.y << std::endl;
    std::cout << "NOD1: " << nodUnitsToChooseSs[0].getPosition().x+( unitsToChooseFromS.getPosition().x ) << "  " << nodUnitsToChooseSs[0].getPosition().y+( unitsToChooseFromS.getPosition().y+chooseScreenDeltaY-260 ) << std::endl;
    std::cout << "NOD2: " << nodUnitsToChooseSs[1].getPosition().x+( unitsToChooseFromS.getPosition().x ) << "  " << nodUnitsToChooseSs[1].getPosition().y+( unitsToChooseFromS.getPosition().y+chooseScreenDeltaY-260 ) << std::endl;

    // unit will be chosen or deleted from chosen ones
    if( _released == sf::Mouse::Button::Right ) {

        // check if any unit has been deleted from the first player chosen
        if( chosenRace == NOD ) {
            // check if any unit has been chosen
            for (int i = 0; i < amountOfNodUnits; ++i) {
                if (nodUnitsToChooseSs[i].getGlobalBounds().contains( mousePos )) {
                    if (chosenUnitsOne.size() < maxOfChosenUnitsToDisplay) {
                        chosenUnitsOne.push_back( std::make_pair< Unit*, const std::string* >( &allNodUnitsDB[i], &nodUnitsDescriptions[i] ));
                        std::cout << "unit " << allNodUnitsDB[i].getNamePtr() << " added to vector" << std::endl;
                    }
                }

            }
            // check if any unit has been deleted from the first player chosen
            for (std::vector< std::pair< Unit*, const std::string* > >::iterator iter = chosenUnitsOne.begin(); iter != chosenUnitsOne.end();) {
                if (iter->first->getPortrait().getGlobalBounds().contains(mousePos)) {
                    iter = chosenUnitsOne.erase(iter);
                } else {
                    ++iter;
                }
            }
        }
        if( chosenRace == GDI ) {
            // check if any unit has been chosen
            for (int i = 0; i < amountOfGniUnits; ++i) {
                if (gniUnitsToChooseSs[i].getGlobalBounds().contains( mousePos )) {
                    if (chosenUnitsTwo.size() < maxOfChosenUnitsToDisplay) {
                        chosenUnitsTwo.push_back( std::make_pair< Unit*, const std::string* >( &allGniUnitsDB[i], &gniUnitsDescriptions[i] ));
                        std::cout << "unit " << allGniUnitsDB[i].getNamePtr() << " added to vector" << std::endl;
                    }
                }

            }
            // check if any unit has been deleted from the second player chosen
            for (std::vector< std::pair< Unit*, const std::string* > >::iterator iter = chosenUnitsTwo.begin(); iter != chosenUnitsTwo.end();) {
                if (iter->first->getPortrait().getGlobalBounds().contains(mousePos)) {
                    iter = chosenUnitsTwo.erase(iter);
                } else {
                    ++iter;
                }
            }
        }
    }

        // we will have description of unit to show
        if( _released == sf::Mouse::Button::Left ) {

            if( playerPortraitSs.first.getGlobalBounds().contains( mousePos ) ){
                chosenRace = NOD;
            }
            if( playerPortraitSs.second.getGlobalBounds().contains( mousePos ) ){
                chosenRace = GDI;
            }

            if( chosenRace == GDI ) {
                for (int i = 0; i < amountOfGniUnits; ++i) {
                    if (gniUnitsToChooseSs[i].getGlobalBounds().contains(mousePos)) {
                        unitDescriptionT.clear(sf::Color::Cyan);
                        portraitOfUnitToDescribe.setTexture(gniUnitsToChooseTs[i]);
                        descriptionOfUnit.setString(gniUnitsDescriptions[i]);
                        unitDescriptionT.draw(descriptionOfUnit);
                        unitDescriptionT.draw(portraitOfUnitToDescribe);
                        unitDescriptionT.display();
                    }
                }
                for( const auto& x : chosenUnitsTwo ){
                    if( x.first->getPortrait().getGlobalBounds().contains( mousePos ) ){
                        unitDescriptionT.clear( sf::Color::Cyan );
                        portraitOfUnitToDescribe.setTexture( *x.first->getPortrait().getTexture() );
                        descriptionOfUnit.setString( *x.second );
                        unitDescriptionT.draw( descriptionOfUnit );
                        unitDescriptionT.draw( portraitOfUnitToDescribe );
                        unitDescriptionT.display();
                    }
                }
            }
            if( chosenRace == NOD ) {
                for (int i = 0; i < amountOfNodUnits; ++i) {
                    if (nodUnitsToChooseSs[i].getGlobalBounds().contains( mousePos )) {
                        unitDescriptionT.clear(sf::Color::Cyan);
                        portraitOfUnitToDescribe.setTexture(nodUnitsToChooseTs[i]);
                        descriptionOfUnit.setString(nodUnitsDescriptions[i]);
                        unitDescriptionT.draw(descriptionOfUnit);
                        unitDescriptionT.draw(portraitOfUnitToDescribe);
                        unitDescriptionT.display();
                    }
                }
                for( const auto& x : chosenUnitsOne ){
                    if( x.first->getPortrait().getGlobalBounds().contains( mousePos ) ){
                        unitDescriptionT.clear( sf::Color::Cyan );
                        portraitOfUnitToDescribe.setTexture( *x.first->getPortrait().getTexture() );
                        descriptionOfUnit.setString( *x.second );
                        unitDescriptionT.draw( descriptionOfUnit );
                        unitDescriptionT.draw( portraitOfUnitToDescribe );
                        unitDescriptionT.display();
                    }
                }
            }
        }
}

void ChoosingScreen::handleInputKeyboard( sf::Keyboard::Key _released )
{
    if( _released == sf::Keyboard::Key::L )
    {
        for( auto& x : chosenUnitsOne )
        {
            std::cout << x.first->getNamePtr() << "  ";
        }
        puts("");
        choosingScreenRunning = false;
    }

}

void ChoosingScreen::run()
{
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while( gameWindowPtr->isOpen() && choosingScreenRunning )
    {
        elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while( timeSinceLastUpdate > TimePerFrame ) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            render();
        }


        // DEBUG

        //#########


    }


    std::cout << "exiting choosing screen..." << std::endl;
}

void ChoosingScreen::render() {
    gameWindowPtr->clear(sf::Color::Black);
    gameWindowPtr->draw(unitsToChooseFromS);
    gameWindowPtr->draw(unitsChosenS);
    for (auto &x : pointsOnMiddleTable)
        gameWindowPtr->draw(x);
    gameWindowPtr->draw(unitDescriptionS);

    // middle table of chosen units

    if( chosenRace == NOD ) {
        for (int i = 0; i < amountOfNodUnits; ++i) {
            gameWindowPtr->draw(nodUnitsToChooseSs[i]);
        }
        if (!chosenUnitsOne.empty()) {
            for (size_t x = 0; x < chosenUnitsOne.size(); ++x) {
                chosenUnitsOne[x].first->getPortrait().setPosition(pointsOnMiddleTable[x].getPosition());
                gameWindowPtr->draw(chosenUnitsOne[x].first->getPortrait());
            }
        }
    }

    else if( chosenRace == GDI ){
        for( int i=0; i<amountOfGniUnits; ++i ){
            gameWindowPtr->draw(gniUnitsToChooseSs[i]);
        }
        if (!chosenUnitsTwo.empty()) {
            for (size_t x = 0; x < chosenUnitsTwo.size(); ++x) {
                chosenUnitsTwo[x].first->getPortrait().setPosition(pointsOnMiddleTable[x].getPosition());
                gameWindowPtr->draw(chosenUnitsTwo[x].first->getPortrait());
            }
        }
    }

    for (int i = 0; i < amountOfUnitTypes; ++i) {
        gameWindowPtr->draw(unitTypes[i]);
    }

    gameWindowPtr->draw( playerPortraitSs.first );
    gameWindowPtr->draw( playerPortraitSs.second );

    gameWindowPtr->display();
}

std::pair< std::vector< Unit >, std::vector<Unit> >* ChoosingScreen::exportChosenUnitsVectors()
{
    auto retPtr = new std::pair< std::vector< Unit >, std::vector<Unit> >;
    for( auto& x : chosenUnitsOne ){
        retPtr->first.push_back( *x.first );
    }
    for( auto& x : chosenUnitsTwo ){
        retPtr->second.push_back( *x.first );
    }
    return retPtr;
};