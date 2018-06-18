//
// Created by Ackan on 14.06.2018.
//

#include <SFML/System.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <map>
#include <string>
#include "units/Unit.h"
#include "gameConstants.h"

#ifndef _CHOOSINGSCREEN_H
#define _CHOOSINGSCREEN_H


#include <SFML/Graphics/RenderWindow.hpp>

class ChoosingScreen {
    const int width;
    const int height;
    sf::RenderWindow* gameWindowPtr;
    sf::Font choosingScreenFont;

    // 3 main divs of choosing screen:
    // 1. for units to choose from
    // 2. for unit chosen
    // 3. for description and statistics of selected unit
    sf::RectangleShape backUToChoose;
    sf::RectangleShape backUChosen;
    sf::RectangleShape backDescOfUnits;

    // array of maps with units of each faction
    std::array< std::map<std::string, Unit>, amountOfRacesInGame > races;

    // untis chosen by first player
    std::vector<Unit> chosenUnitsOne;

    // untis chosen by second player
    std::vector<Unit> chosenUnitsTwo;

    // portraits of players to display at the top of screen
    std::pair<sf::Sprite, sf::Sprite> playerPortraits;

    sf::RectangleShape tableColumns[3];
    sf::RectangleShape tableRows[4];

    static const sf::Time	TimePerFrame;
    void initLoad();

public:
    explicit ChoosingScreen( sf::RenderWindow* _winPtr, int _width, int _height );

    void processEvents();
    void run();
    void render();

};


#endif //_CHOOSINGSCREEN_H
