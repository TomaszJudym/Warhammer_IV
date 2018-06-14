//
// Created by Jebac Microsoft on 2/23/2018.
//

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
const int windowWidth = 1024;
const int windowHeight = 768;
const int unitHeight = 120;
const int unitWidth = 100;
const float escapeCombatMove = 30.0;
const int barWidth = unitWidth;
const int barHeight = 5;
const float outlineThickness = 5.f;
const float healthBarYfit = 70.f;
const short amountOfTextIconsInMainMenu = 3;
const short amountOfTextIconsInOptionsMenu = 3;
const short amountOfTextIconsInOptionsSoundMenu = 4;
const short amountOfTextIconInOptionsVideoMenu = 4;
const short amountOfTextIconsInOptionsInputMenu = 4;


#endif //_GAMECONSTANTS_H_
