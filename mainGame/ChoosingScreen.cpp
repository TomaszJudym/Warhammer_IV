//
// Created by Ackan on 14.06.2018.
//

#include "ChoosingScreen.h"
#include "choosingScreenInitLoad.inl"

const sf::Time ChoosingScreen::TimePerFrame = sf::seconds(1.f/60.f);

ChoosingScreen::ChoosingScreen(sf::RenderWindow* _winPtr, int _width, int _height)
: gameWindowPtr( _winPtr ),
  width( _width ),
  height( _height )
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
            case sf::Event::MouseButtonReleased:
               // TODO handlePlayerInputMouse( event.mouseButton.button, true );
                break;

            case sf::Event::Closed:
                gameWindowPtr->close();
                break;
        }
    }
}

void ChoosingScreen::run()
{
    sf::Clock clock;
    sf::Clock mainClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while( gameWindowPtr->isOpen() )
    {
        processEvents();
        render();
    }
}

void ChoosingScreen::render()
{
    gameWindowPtr->clear( sf::Color::Black );
    gameWindowPtr->draw( backUToChoose );
    gameWindowPtr->draw( backUChosen );
    gameWindowPtr->draw( backDescOfUnits );
    gameWindowPtr->display();
}