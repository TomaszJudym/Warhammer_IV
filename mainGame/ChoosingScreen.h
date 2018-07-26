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
#include <tuple>
#include <random>
#include "UnitMenuStatistics/UnitMenuStatistics.h"
#include "stringHelper.h"
#include "units/Unit.h"
#include "gameConstants.h"

#ifndef _CHOOSINGSCREEN_H
#define _CHOOSINGSCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>



class ChoosingScreen {
    const bool FIRST_ARMY = 1;
    const bool SECOND_ARMY = 0;
    int chooseScreenDeltaY;
    short amountOfChosenUnitsToDisplay;
    short maxOfChosenUnitsToDisplay;
    RACES chosenRace;
    bool choosingScreenRunning;
    std::array< Unit, amountOfNodUnits> allNodUnitsDB;
    std::array< Unit, amountOfGniUnits> allGniUnitsDB;
    static UnitMenuStatistics unitMenuStatisticsNodDB[amountOfNodUnits];
    static UnitMenuStatistics unitMenuStatisticsGniDB[amountOfGniUnits];
    UnitMenuStatistics* unitStatisticsToDisplay;
    static UnitStatisticsIcons unitStatsIcons;
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
    sf::Vector2f statsPoint;
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
    std::vector< std::tuple< Unit*, const std::string* , UnitMenuStatistics* > > chosenUnitsOne;

    // untis chosen by second player
    std::vector< std::tuple< Unit*, const std::string* , UnitMenuStatistics* > > chosenUnitsTwo;

    // portraits of players to display at the top of screen
    std::pair< sf::Texture, sf::Texture > playerPortraitTs;
    std::pair< sf::Sprite, sf::Sprite > playerPortraitSs;

    static const sf::Time TimePerFrame;

    void initLoad();

public:
    explicit ChoosingScreen( sf::RenderWindow* _winPtr, int _width, int _height );
    void handleInputMouseScroll( float _scrollDelta );
    void handleInputMouse( sf::Mouse::Button _released );
    void handleInputKeyboard( sf::Keyboard::Key _released );
    void changeChooseRaceTo( RACES _race );
    void processEvents();
    void run();
    void render();
    void exit();
    std::pair< std::vector< Unit >, std::vector<Unit> >* exportChosenUnitsVectors();
    std::array<std::string, amountOfNodUnits> nodUnitsDescriptions;
    std::array<std::string, amountOfGniUnits> gniUnitsDescriptions;
};


#endif //_CHOOSINGSCREEN_H
