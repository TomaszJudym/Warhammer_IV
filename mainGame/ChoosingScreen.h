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
#include <array>
#include "stringHelper.h"
#include "units/Unit.h"
#include "gameConstants.h"

#ifndef _CHOOSINGSCREEN_H
#define _CHOOSINGSCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>



class ChoosingScreen {
    int chooseScreenDeltaY;
    short amountOfChosenUnitsToDisplay;

    std::array<Unit, amountOfNodUnits> allNodUnitsDB;

    const int width;
    const int height;
    sf::RenderWindow* gameWindowPtr;
    sf::Font choosingScreenFont;
    //########################################
    // left div with units to choose from
    sf::RenderTexture unitsToChooseFromRT;
    sf::Sprite unitsToChooseFromS;

    // left menu of units to choose from
    sf::Text unitTypes[amountOfUnitTypes];

    // NOD UNITS PORTRAITS
     sf::Texture nodUnitsToChooseTs[amountOfNodUnits];
     sf::Sprite nodUnitsToChooseSs[amountOfNodUnits];

    // NOD UNITS PORTRAITS
    sf::Texture gniUnitsToChooseTs[amountOfNodUnits];
    sf::Sprite gniUnitsToChooseSs[amountOfNodUnits];

    //########################################

    //########################################
    // middle div with already chosen units
    sf::Texture unitsChosenT;
    sf::Sprite unitsChosenS;

    std::array<sf::Sprite*, 18> chosenUnitsToDisplay;
    sf::RectangleShape pointsOnMiddleTable[18];
    //########################################

    //########################################
    // right div with units description
    sf::RenderTexture unitDescriptionT;
    sf::Sprite unitDescriptionS;
    sf::Sprite portraitOfUnitToDescribe;
    sf::Text descriptionOfUnit;

    // TODO separate object for units bars with stats
    //########################################

    // array of maps with units of each faction
    std::array< std::map<std::string, Unit>, amountOfRacesInGame > races;

    // untis chosen by first player
    std::vector<Unit> chosenUnitsOne;

    // untis chosen by second player
    std::vector<Unit> chosenUnitsTwo;

    // portraits of players to display at the top of screen
    std::pair<sf::Sprite, sf::Sprite> playerPortraits;

    static const sf::Time	TimePerFrame;

    void initLoad();

public:
    explicit ChoosingScreen( sf::RenderWindow* _winPtr, int _width, int _height );
    void handleInputMouseScroll( float _scrollDelta );
    void handleInputMouse( sf::Mouse::Button _released );
    void handleInputKeyboard( sf::Keyboard::Key _released );
    void processEvents();
    void run();
    void render();
    const std::array<std::string, amountOfNodUnits> nodUntisdescriptions;
};


#endif //_CHOOSINGSCREEN_H
