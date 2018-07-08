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
  amountOfChosenUnitsToDisplay(0)
  //allNodUnitsDB()
{
    initLoad();

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
        // check if any unit has been chosen
        for (int i = 0; i < amountOfNodUnits; ++i) {
            if (nodUnitsToChooseSs[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                std::cout << "Chosen unit at x: " << nodUnitsToChooseSs[i].getPosition().x << " y: "
                          << nodUnitsToChooseSs[i].getPosition().y << std::endl;
                if (chosenUnitsOne.size() < 18) {
                    chosenUnitsOne.push_back(allNodUnitsDB[i]);
                }
                std::cout << "Unit " << allNodUnitsDB[i].getNamePtr() << " added to chosen_NOD_untis" << std::endl;
                std::cout << "UNITS VECTOR: ";
                for (auto &i : chosenUnitsOne) {
                    std::cout << i.getNamePtr() << " | ";
                    puts("");
                }
            }

        }
        // check if any unit has been deleted from chosen ones
        for (std::vector<Unit>::iterator iter = chosenUnitsOne.begin(); iter != chosenUnitsOne.end();) {
            if (iter->getPortrait().getGlobalBounds().contains(mousePos)) {
                iter = chosenUnitsOne.erase(iter);
            } else {
                ++iter;
            }
        }
    }

        // we will have description of unit to show
        if( _released == sf::Mouse::Button::Left )
        {
            bool alreadySomethingToDisplay = false;
            for( int i=0; i<amountOfNodUnits; ++i )
            {
                if( nodUnitsToChooseSs[i].getGlobalBounds().contains( mousePos ) ){
                    unitDescriptionS = nodUnitsToChooseSs[i];
                    unitDescriptionT.draw( unitDescriptionS );
                    descriptionOfUnit.setString( "lol" );
                    unitDescriptionT.draw( descriptionOfUnit );
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
            std::cout << x.getNamePtr() << "  ";
        }
        puts("");
    }
}

void ChoosingScreen::run()
{
    while( gameWindowPtr->isOpen() )
    {
        processEvents();
        render();
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

    if (!chosenUnitsOne.empty()) {
        for (size_t x = 0; x < chosenUnitsOne.size(); ++x) {
            chosenUnitsOne[x].getPortrait().setPosition(pointsOnMiddleTable[x].getPosition());
            gameWindowPtr->draw(chosenUnitsOne[x].getPortrait());
        }

    }

    for (int i = 0; i < amountOfNodUnits; ++i) {
        gameWindowPtr->draw(nodUnitsToChooseSs[i]);
    }

    for (int i = 0; i < amountOfUnitTypes; ++i) {
        gameWindowPtr->draw(unitTypes[i]);
    }

    gameWindowPtr->display();
}