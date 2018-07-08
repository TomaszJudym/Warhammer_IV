//
// Created by Jebac Microsoft on 3/17/2018.
//
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cctype>
#include <cstdint>
#include "../../gameConstants.h"

#ifndef WARHAMMER_II_HEALTHBAR_H
#define WARHAMMER_II_HEALTHBAR_H


class HealthBar {
    sf::RectangleShape bar;
    sf::RectangleShape outline;
    int percentageHpLost;
    int health;
    int fullHealth;
    sf::Color color;
    sf::Vector2f position;
public:
    HealthBar& operator=( const HealthBar& _healthBar );
    explicit HealthBar( int _health, sf::Color _color = sf::Color::Cyan );
    HealthBar( const HealthBar& _another );
    sf::RectangleShape& getBar();
    sf::RectangleShape& getOutline();
    sf::Vector2f& getPosition();
    sf::Vector2f getPosition() const;
    int* getHP();
    void move( float _x, float _y );
    void setPosition( const sf::Vector2f& _newPos );
    void increase( float& _amount );
    void decrease( float& _amount );
};


#endif //WARHAMMER_II_HEALTHBAR_H
