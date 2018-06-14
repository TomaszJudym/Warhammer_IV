#include "Unit.h"
#include "../gameConstants.h"
#ifndef _UNITADDS_
#define _UNITADDS_

void Unit::initLoad()
{
    pointRect.setFillColor( sf::Color::Red );
    pointRect.setOrigin( 2.0, 2.0 );
    combatChecker.setFillColor( sf::Color::Magenta );
    combatChecker.setSize( sf::Vector2f( unitWidth, unitHeight-20 ) );
    combatChecker.setOrigin( sf::Vector2f( unitWidth/2, unitHeight/2 ) );
}



#endif