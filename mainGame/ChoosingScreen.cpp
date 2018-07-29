//
// Created by Ackan on 14.06.2018.
//

#include "ChoosingScreen.h"
#include "choosingScreenInitLoad.inl"
#include "gameConstants.h"

const sf::Time ChoosingScreen::TimePerFrame = sf::seconds(1.f/60.f);

std::random_device rd;
std::mt19937 mt( rd() );
std::uniform_int_distribution<short> dist( 1, 100 );

UnitStatisticsIcons ChoosingScreen::unitStatsIcons;
UnitMenuStatistics ChoosingScreen::unitMenuStatisticsNodDB[] = {
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons },
        { dist(mt), dist(mt), dist(mt), dist(mt), dist(mt), unitStatsIcons }
};
// TODO make it smarter ;_;
UnitMenuStatistics ChoosingScreen::unitMenuStatisticsGniDB[] = {
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons },
        { 100, 90, 80, 70, 60, unitStatsIcons }
};

ChoosingScreen::ChoosingScreen(sf::RenderWindow* _winPtr, int _width, int _height)
: gameWindowPtr( _winPtr ),
  width( _width ),
  height( _height ),
  chooseScreenDeltaY(130),
  amountOfChosenUnitsToDisplay(0),
  maxOfChosenUnitsToDisplay(18),
  chosenRace(NOD),
  choosingScreenRunning( true ),
  statsPoint( 700.f, 400.f ),
  unitStatisticsToDisplay(nullptr)
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

                // DEBUG PURPOSES

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
    // unit will be chosen or deleted from chosen ones
    if( _released == sf::Mouse::Button::Right ) {

        // check if any unit has been deleted from the first player chosen
        if( chosenRace == NOD ) {
            // check if any unit has been chosen
            for (int i = 0; i < amountOfNodUnits; ++i) {
                if (nodUnitsToChooseSs[i].getGlobalBounds().contains( mousePos )) {
                    if (chosenUnitsOne.size() < maxOfChosenUnitsToDisplay) {
                        chosenUnitsOne.push_back( std::make_tuple< Unit*, const std::string*, UnitMenuStatistics* >( &allNodUnitsDB[i], &nodUnitsDescriptions[i], &unitMenuStatisticsNodDB[i] ));
                        std::cout << "unit " << allNodUnitsDB[i].getNamePtr() << " added to vector" << std::endl;
                    }
                }

            }
            // check if any unit has been deleted from the first player chosen
            for (  std::vector< std::tuple< Unit*, const std::string*, UnitMenuStatistics* > >::iterator iter = chosenUnitsOne.begin(); iter != chosenUnitsOne.end(); ) {
                if ( std::get<0>( *iter )->getPortrait().getGlobalBounds().contains(mousePos)) {
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
                        chosenUnitsTwo.push_back( std::make_tuple< Unit*, const std::string*, UnitMenuStatistics* >( &allGniUnitsDB[i], &gniUnitsDescriptions[i], &unitMenuStatisticsGniDB[i] ));
                        std::cout << "unit " << allGniUnitsDB[i].getNamePtr() << " added to vector" << std::endl;
                    }
                }

            }
            // check if any unit has been deleted from the second player chosen
            for (std::vector< std::tuple< Unit*, const std::string*, UnitMenuStatistics* > >::iterator iter = chosenUnitsTwo.begin(); iter != chosenUnitsTwo.end();) {
                if ( std::get<0>( *iter )->getPortrait().getGlobalBounds().contains(mousePos)) {
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
                        unitStatisticsToDisplay = &unitMenuStatisticsGniDB[i];
                        unitDescriptionT.draw(descriptionOfUnit);
                        unitDescriptionT.draw(portraitOfUnitToDescribe);
                        unitDescriptionT.display();
                    }
                }
                for( const auto& x : chosenUnitsTwo ){
                    if( std::get<0>(x)->getPortrait().getGlobalBounds().contains( mousePos ) ){
                        unitDescriptionT.clear( sf::Color::Cyan );
                        portraitOfUnitToDescribe.setTexture( *std::get<0>( x )->getPortrait().getTexture() );
                        descriptionOfUnit.setString( *std::get<1>( x ) );
                        unitStatisticsToDisplay = std::get<2>( x );
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
                        unitStatisticsToDisplay = &unitMenuStatisticsNodDB[i];
                        unitDescriptionT.draw(descriptionOfUnit);
                        unitDescriptionT.draw(portraitOfUnitToDescribe);
                        unitDescriptionT.display();
                    }
                }
                for( const auto& x : chosenUnitsOne ){
                    if( std::get<0>(x)->getPortrait().getGlobalBounds().contains( mousePos ) ){
                        unitDescriptionT.clear( sf::Color::Cyan );
                        portraitOfUnitToDescribe.setTexture( *std::get<0>( x )->getPortrait().getTexture() );
                        descriptionOfUnit.setString( *std::get<1>( x ) );
                        unitStatisticsToDisplay = std::get<2>( x );
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
            std::cout << std::get<0>( x )->getNamePtr() << "  ";
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
                 std::get<0>( chosenUnitsOne[x] )->getPortrait().setPosition(pointsOnMiddleTable[x].getPosition());
                gameWindowPtr->draw( std::get<0>( chosenUnitsOne[x] )->getPortrait());
            }
        }
    }

    else if( chosenRace == GDI ){
        for( int i=0; i<amountOfGniUnits; ++i ){
            gameWindowPtr->draw(gniUnitsToChooseSs[i]);
        }
        if (!chosenUnitsTwo.empty()) {
            for (size_t x = 0; x < chosenUnitsTwo.size(); ++x) {
                std::get<0>( chosenUnitsTwo[x] )->getPortrait().setPosition(pointsOnMiddleTable[x].getPosition());
                gameWindowPtr->draw( std::get<0>( chosenUnitsTwo[x] )->getPortrait());
            }
        }
    }

    for (int i = 0; i < amountOfUnitTypes; ++i) {
        gameWindowPtr->draw(unitTypes[i]);
    }

    gameWindowPtr->draw( playerPortraitSs.first );
    gameWindowPtr->draw( playerPortraitSs.second );
    if( unitStatisticsToDisplay ) {
        unitStatisticsToDisplay->setPosition(statsPoint.x, statsPoint.y);
        unitStatisticsToDisplay->draw(gameWindowPtr);
    }

    gameWindowPtr->display();
}

std::pair< std::vector< Unit >, std::vector<Unit> >* ChoosingScreen::exportChosenUnitsVectors()
{
    auto retPtr = new std::pair< std::vector< Unit >, std::vector<Unit> >;
    for( auto& x : chosenUnitsOne ){
        retPtr->first.push_back( *std::get<0>( x ) );
    }
    for( auto& x : chosenUnitsTwo ){
        retPtr->second.push_back( *std::get<0>( x ) );
    }
    return retPtr;
};