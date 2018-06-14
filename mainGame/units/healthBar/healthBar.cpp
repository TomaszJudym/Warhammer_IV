//
// Created by Jebac Microsoft on 3/17/2018.
//
#include "healthBar.h"

HealthBar::HealthBar( int _health, sf::Color _color )
: health(_health)
  ,color(_color)
  ,percentageHpLost(0)
  ,fullHealth(_health)
{
    bar.setSize( sf::Vector2f( barWidth, barHeight ) );
    outline.setSize( sf::Vector2f( barWidth, barHeight ) );
    bar.setFillColor( color );
    outline.setFillColor( sf::Color::Black );
    outline.setOutlineThickness( outlineThickness );
    outline.setFillColor( sf::Color::White );
}

sf::RectangleShape& HealthBar::getOutline()
{
    return outline;
}

sf::RectangleShape& HealthBar::getBar()
{
    return bar;
}

void HealthBar::setPosition( const sf::Vector2f& _newPos )
{
    outline.setPosition( _newPos );
    bar.setPosition( _newPos );
}


void HealthBar::increase( float& _amount )
{
    health += _amount;
    percentageHpLost -= unitWidth - ( (health*unitWidth)/fullHealth );
    bar.setSize( sf::Vector2f( unitWidth-percentageHpLost, barHeight  ) );
}
void HealthBar::decrease( float& _amount )
{
    if( (health - _amount > 0) ) {
        health -= _amount;
        percentageHpLost += (_amount*unitWidth)/fullHealth;
        bar.setSize(sf::Vector2f(unitWidth - percentageHpLost, barHeight ));
    }
    if( health - _amount <= 0 )
    {
        health = 0;
        percentageHpLost = fullHealth;
        bar.setSize( sf::Vector2f( unitWidth, barHeight ) );
        bar.setFillColor( sf::Color::Red );
    }
}

void HealthBar::move( float _x, float _y )
{
    outline.move( _x, _y );
    bar.move( _x, _y );
}

HealthBar& HealthBar::operator=( const HealthBar& _healthBar )
{
    if( this == &_healthBar )
    {
       return *this;
    }
    else
    {
        bar = _healthBar.bar;
        outline = _healthBar.outline;
        percentageHpLost = _healthBar.percentageHpLost;
        health = _healthBar.health;
        fullHealth = _healthBar.fullHealth;
        color = _healthBar.color;
        position = _healthBar.position;
        setPosition( position );
    }
}

int* HealthBar::getHP()
{
    return &health;
}

sf::Vector2f& HealthBar::getPosition()
{
    return position;
}

sf::Vector2f HealthBar::getPosition() const
{
    return position;
}