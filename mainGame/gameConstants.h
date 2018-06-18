//
// Created by Jebac Microsoft on 2/23/2018.
//

#include <SFML/System/Vector2.hpp>

#ifndef _GAMECONSTANTS_H_
#define _GAMECONSTANTS_H_

enum GAME_STATE{
    MAIN_MENU,
    OPTIONS_MENU,
    OPTIONS_SOUND_MENU,
    OPTIONS_VIDEO_MENU,
    OPTIONS_INPUT_MENU,
    MAIN_GAME
};

enum RACES{
    GDI,
    NOD
};
// WINDOW
const int windowWidth = 1024;
const int windowHeight = 768;

// UNITS
const int unitHeight = 120;
const int unitWidth = 100;
const float escapeCombatMove = 30.0;

// HEALTHBAR
const int barWidth = unitWidth;
const int barHeight = 5;
const float outlineThickness = 5.f;
const float healthBarYfit = 70.f;

// MAIN AND SUB MENUS
const short amountOfTextIconsInMainMenu = 3;
const short amountOfTextIconsInOptionsMenu = 3;
const short amountOfTextIconsInOptionsSoundMenu = 4;
const short amountOfTextIconInOptionsVideoMenu = 4;
const short amountOfTextIconsInOptionsInputMenu = 4;

// CHOOSING MENU
const short amountOfRacesInGame = 2;

const float backOfUToChooseSizeX = 300.f;
const float backOfUToChooseSizeY = windowHeight;
const float backDescOfUnitsSizeX = 350.f;
const float backDescOfUnitsSizeY = windowHeight;
const float backUChosenSizeX = 300.f;
const float backUChosenSizeY = windowHeight;

#endif //_GAMECONSTANTS_H_
