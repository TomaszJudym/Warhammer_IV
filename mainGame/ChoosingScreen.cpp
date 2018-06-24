//
// Created by Ackan on 14.06.2018.
//

#include "ChoosingScreen.h"
#include "choosingScreenInitLoad.inl"

const sf::Time ChoosingScreen::TimePerFrame = sf::seconds(1.f/60.f);

ChoosingScreen::ChoosingScreen(sf::RenderWindow* _winPtr, int _width, int _height)
: gameWindowPtr( _winPtr ),
  width( _width ),
  height( _height ),
  chooseScreenDeltaY(130),
  amountOfChosenUnitsToDisplay(0)
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
    gameWindowPtr->display();
}
