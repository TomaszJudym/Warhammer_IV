//
// Created by Jebac Microsoft on 1/30/2018.
//

#ifndef GAME_H_
#define GAME_H_

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <vector>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <chrono>
#include "MainMenu.h"
#include "gameConstants.h"
#include "units/Unit.h"


class Game : private sf::NonCopyable
{
public:

    Game();
    void					run();
    void        check_units_combat_status();
    void        units_fight();
    short       framesToNextAttack;
    bool isInMainMenu;


private:
    // loading all necessary files inside inline file
    void                    initLoad();
    // changing positions and states of entites
    void					processEvents();
    // drawing positioned sprites on screen
    void					render();
    // updating position of units
    void                    update(sf::Time deltaTime);




    void					updateStatistics(sf::Time _elapsedTime, sf::Time _mainTime);
    void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void                    handlePlayerInputMouse(sf::Mouse::Button button, bool isPressed);



    static const sf::Time	TimePerFrame;

    sf::RenderWindow		gameWindow;

    // mainMenu, like run void inside game main run void, to display start, options and exit
    // player should be able to come back to it after pressing back button
    MainMenu mainGameMenu;

    std::vector<Unit>       units;
    Unit*                   choosedUnit;
    sf::Font				gameFont;
    sf::Text				statisticsText;
    sf::Text                statisticsMainGameTime;
    sf::Time				statisticsUpdateTime;
    sf::Time                mainTime;
    std::size_t				statisticsNumFrames;

    //TESTING AREA
    sf::Texture unit1, unit2, unit3, unit4, unit5;
    sf::Sprite guardsman, guardsman2, guardsman3, guardsman4, guardsman5;
    sf::RectangleShape choosedUnitBorder;
    sf::RectangleShape combatChecker;
    sf::Vector2f getUnitCombatDirection( const Unit* _attacker, const Unit* _target);
    bool unitsAreInCombat( const Unit* _attacker, const Unit* _target );
    void unitsEnterCombat( Unit* _attacker, Unit* _defender );
    bool unitCanMove( Unit* _entity );
    bool canEscapeFromCombat( const Unit* _entity );
    //============================
};

#endif //GAME_H_
