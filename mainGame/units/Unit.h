//
// Created by Jebac Microsoft on 2/11/2018.
//
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <vector>
#include <cstring>
#include "healthBar/healthBar.h"
#include "../gameConstants.h"
#ifndef _UNIT_H
#define _UNIT_H

class Unit {
private:
    /*
     * ENUMS ++++++++++++++++++++++++++++++++++++++++++++++++++
     */
    enum goingOut{
        left,
        right,
        up,
        down
    };
    enum state{
        moving,
        holdToBorder,
        borderEscape,
        stopped,
        combat
    };
    /*
     *        ++++++++++++++++++++++++++++++++++++++++++++++++++
     */
    char* name;

    const static float unitSpeed;
    short           hp;
    float           firepower;
    sf::Sprite portrait;
    bool            selected;
    bool            outOfBorder;
    bool            inCombat;


    bool            escapesFromCombat;
    short team;
    sf::Vector2f    deltas;
    sf::Vector2f    deltasToEscape;
    sf::Vector2f    borderDeltas;
    sf::Vector2f    point, enterBorderPoint;
    sf::RectangleShape pointRect;
    sf::RectangleShape combatChecker;
    goingOut        escape;
    state           currentState;
    HealthBar       healthBar;
public:
    explicit Unit( sf::Sprite&,
                   char* _name = (char*)"undefined",
                   int _hp = 100,
                   float _fp = 100.f,
                   short _team=1 );
    sf::Vector2f& getPoint();
    const sf::Vector2f& getDeltas() const;
    const sf::Vector2f  getEscapeDeltas() const;
    void selectOn();
    void selectOff();
    bool isSelected();

    // OPERATORS
    Unit& operator=( const Unit& _unit );

    // COMBAT
    std::vector<Unit*> enemies;
    bool&           combatStatus();
    //======================
    void            enterCombat(Unit* _against);
    void            exitCombat();
    void            fight();
    void            changeHp( float _delta );
    void            die();
    void            clearEnemiesVector();


    // HEALTH BAR

    sf::RectangleShape& getHealthBar();
    sf::RectangleShape& getHealthOutline();
    HealthBar& getMainHealthBar();
    HealthBar getMainHealthBar() const;

    short getHP();
    char* getNamePtr() const;

    sf::Sprite& getPortrait();
    sf::Sprite getPortrait() const;
    sf::RectangleShape& getPointRect();
    sf::RectangleShape& getCombatChecker();
    void move();
    bool moveAtBorder();
    void setDeltas( sf::Vector2f _newDeltas );
    void setDeltas( float _x, float _y );
    void setMovingPoint( float _x, float _y );
    void setMovingPoint( sf::Vector2f& xy );
    bool checkBorders();
    state checkState();
    // function to separate loading data to unit at initialization
    void initLoad();

    ~Unit();
};

#endif //WARHAMMER_II_UNIT_H
