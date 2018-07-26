#include "../Game.h"
#include "loader.h"
#include "../gameConstants.h"
const sf::Vector2f cardSize = { 120, 110 };



void Game::initLoad()
{
    loader(&gameFont, "font/Consolas.ttf" );

    combatChecker.setFillColor( sf::Color::Magenta );
    combatChecker.setSize( sf::Vector2f( unitWidth/4, unitHeight/4 ) );
    combatChecker.setOrigin( sf::Vector2f( (unitWidth/4)/2, (unitHeight/4)/2 ) );
    combatChecker.setPosition(0.f, 0.f);

    // initializing statistics text in top left corner
    statisticsText.setFont( gameFont );
    statisticsText.setPosition(5.f, 5.f);
    statisticsText.setCharacterSize(10);
    statisticsMainGameTime.setFont( gameFont );
    statisticsMainGameTime.setPosition( 5.f, 30.f );
    statisticsMainGameTime.setCharacterSize( 10 );

    // setting portraits of units


    // setting outline of currently choosed unit
    choosedUnitBorder.setSize( sf::Vector2f( unitWidth, unitWidth) );
    choosedUnitBorder.setFillColor( sf::Color::Cyan );
    choosedUnitBorder.setOrigin( unitWidth/2, unitWidth/2 );

    // setting positions units received from choosing screen
    int unitsPositionsIter=1;
    int unitsIter=0;
    // first army
    for( ;unitsPositionsIter<positionsOfUnitsOne.size()/2; ++unitsPositionsIter, ++unitsIter ){
        positionsOfUnitsOne[unitsIter].x = unitsPositionsIter*unitWidth+unitsPositionsIter*30.f;
        positionsOfUnitsOne[unitsIter].y = unitHeight+30.f;
    }
    unitsPositionsIter=1;
    for( ;unitsPositionsIter<positionsOfUnitsOne.size(); ++unitsPositionsIter, ++unitsIter ){
        positionsOfUnitsOne[unitsIter].x = unitsPositionsIter*unitWidth+unitsPositionsIter*30.f;
        positionsOfUnitsOne[unitsIter].y = unitHeight*2+30.f;
    }
    unitsPositionsIter=1;
    unitsIter=0;
    //second army
    for( ;unitsPositionsIter<positionsOfUnitsTwo.size()/2; ++unitsPositionsIter, ++unitsIter ){
        positionsOfUnitsTwo[unitsIter].x = unitsPositionsIter*unitWidth+unitsPositionsIter*30.f;
        positionsOfUnitsTwo[unitsIter].y = windowHeight-unitHeight*2+30.f*2;
    }
    unitsPositionsIter=1;
    for( ;unitsPositionsIter<positionsOfUnitsTwo.size(); ++unitsPositionsIter, ++unitsIter ){
        positionsOfUnitsTwo[unitsIter].x = unitsPositionsIter*unitWidth+unitsPositionsIter*30.f;
        positionsOfUnitsTwo[unitsIter].y = windowHeight-(unitHeight+30.f);
    }


}