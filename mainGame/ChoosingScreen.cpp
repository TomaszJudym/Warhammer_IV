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
  allGniUnitsDB ({
        Unit( nodUnitsToChooseSs[ attack_bike ],
              (char*)"Attack bike",
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ militant ],
              const_cast<char*>("Militant"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ avatar ],
             const_cast<char*>("Avatar"),
             100,
             10.f,
             1),

        Unit( nodUnitsToChooseSs[ carryall ],
              const_cast<char*>("Carryall"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ commando ],
              const_cast<char*>("Commando"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ fanatic ],
              const_cast<char*>("Fanatic"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ flame_tank ],
              const_cast<char*>("Flame tank"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ black_hand ],
              const_cast<char*>("Black hand"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ shadow ],
              const_cast<char*>("Shadow"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ scorp ],
              const_cast<char*>("Scorpion tank"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ saboteur ],
              const_cast<char*>("Saboteur"),
              100,
              10.f,
              1),

        Unit( nodUnitsToChooseSs[ rocket ],
              const_cast<char*>("Rocket soldier"),
              100,
              10.f,
              1),

} )
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
    if( _released == sf::Mouse::Button::Right )
    {
        std::cout << "RMB clicked" << std::endl;
        for( int i=0; i<amountOfNodUnits; ++i )
        {

            if( nodUnitsToChooseSs[i].getGlobalBounds().contains( mousePos ) )
            {
                chosenUnitsOne.emplace_back( allGniUnitsDB[i] );
                std::cout << "Unit " << allGniUnitsDB[i].getNamePtr() << " added to choosen NOD untis" << std::endl;
            } // TODO: some random choosing
        }
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

void ChoosingScreen::render()
{
    gameWindowPtr->clear(sf::Color::Black);
    gameWindowPtr->draw( unitsToChooseFromS );
    gameWindowPtr->draw( unitsChosenS );
    for( auto& x : pointsOnMiddleTable )
        gameWindowPtr->draw( x );
    gameWindowPtr->draw( pointsOnMiddleTable[0] );
    gameWindowPtr->draw( unitDescriptionS );

    // middle table of chosen units

    for( size_t chosenUnitsIter=0; chosenUnitsIter < chosenUnitsOne.size(); ++chosenUnitsIter )
    {
        chosenUnitsOne[chosenUnitsIter].getPortrait().setPosition( pointsOnMiddleTable[chosenUnitsIter].getPosition() );
        gameWindowPtr->draw( chosenUnitsOne[chosenUnitsIter].getPortrait() );
    }


    gameWindowPtr->display();
}
