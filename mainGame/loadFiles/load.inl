#include "../Game.h"
#include "loader.h"
#include "../gameConstants.h"
const sf::Vector2f cardSize = { 120, 110 };



void Game::initLoad()
{
    // test units
   /* loader(&unit1, gniUnitsPaths[ gniUnits::juggernaut ]);
    loader(&unit2, nodUnitsPaths[ nodUnits::avatar ]);
    loader(&unit3, nodUnitsPaths[ nodUnits::black_hand ]);
    loader(&unit4, gniUnitsPaths[gniUnits::colos ]);
    loader(&unit5, gniUnitsPaths[gniUnits::bwp]); */
    loader(&gameFont, "font/Consolas.ttf" );

    combatChecker.setFillColor( sf::Color::Magenta );
    combatChecker.setSize( sf::Vector2f( unitWidth/2, unitHeight/2-20.f ) );
    combatChecker.setOrigin( sf::Vector2f( unitWidth/2, unitHeight/2 ) );
    combatChecker.setPosition(0.f, 0.f);

    // initializing statistics text in top left corner
    statisticsText.setFont( gameFont );
    statisticsText.setPosition(5.f, 5.f);
    statisticsText.setCharacterSize(10);
    statisticsMainGameTime.setFont( gameFont );
    statisticsMainGameTime.setPosition( 5.f, 30.f );
    statisticsMainGameTime.setCharacterSize( 10 );

    // setting portraits of units
    guardsman.setTexture( unit1 );
    guardsman2.setTexture( unit2 );
    guardsman3.setTexture( unit3 );
    guardsman4.setTexture( unit4 );
    guardsman5.setTexture( unit5 );


    // setting outline of currently choosed unit
    choosedUnitBorder.setSize( sf::Vector2f( 100, 80 ) );
    choosedUnitBorder.setFillColor( sf::Color::Cyan );
    choosedUnitBorder.setOrigin( 50, 40 );

    // initializing units vector
    // respectively:            hp | firepower | team
  /*  units.emplace_back( guardsman, (char*)"juggernaut", 150, 10.f, 1 );
    units.emplace_back( guardsman2, (char*)"avatar", 150, 10.f, 2 );
    units.emplace_back( guardsman3, (char*)"black hand", 150, 10.f, 2);
    units.emplace_back( guardsman4, (char*)"colos", 150,  10.f,  1 );
    units.emplace_back( guardsman5, (char*)"bwp", 150 , 10.f, 2 ); */
    // setting units origin to middle of unit portrait
  /*  for( auto& i : units )
    {
        i.getPortrait().setOrigin( cardSize.x/2, cardSize.y/2 );
    }
    // setting default untis positions
    units[0].getPortrait().setPosition( 150.f, 100.f );
    units[1].getPortrait().setPosition( 300.f, 300.f );
    units[2].getPortrait().setPosition(450.f, 300.f);
    units[3].getPortrait().setPosition( 600.f, 300.f );
    units[4].getPortrait().setPosition( 750.f, 300.f );
    // setting start positions of unit health bars
    for( auto& i : units )
    {
        i.getMainHealthBar().setPosition( sf::Vector2f(i.getPortrait().getPosition().x-(unitWidth/2), i.getPortrait().getPosition().y-healthBarYfit) );
    }
    */
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