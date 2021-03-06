//
// Created by Jebac Microsoft on 2/23/2018.
//

#include <SFML/System/Vector2.hpp>
#include <array>

#ifndef _GAMECONSTANTS_H_
#define _GAMECONSTANTS_H_

#include "units/Unit.h"



enum GAME_STATE{
    MAIN_MENU,
    OPTIONS_MENU,
    OPTIONS_SOUND_MENU,
    OPTIONS_VIDEO_MENU,
    OPTIONS_INPUT_MENU,
    MAIN_GAME
};

enum UNIT_TYPES{
    HERO_UNITS,
    MELEE_UNITS,
    RANGE_UNITS,
    ELITE_UNITS,
    SIEGE_UNITS,
    MONSTERS
};

enum RACES{
    GDI,
    NOD
};

const short amountOfUnitStatistics = 5;
const short statisticsBarWidth = 200;
const short statisticsBarHeight = 30;
const short statisticsHeight = 300;
const short statisticsWidth = 300;

enum{
    HP,
    FIREPOWER,
    ARMOR,
    SPEED,
    AGILITY
};
// WINDOW
const int windowWidth = 1024;
const int windowHeight = 768;

// UNITS
const short unitHeight = 120;
const short unitWidth = 100;

const short choosedUnitWidth = 60;
const short choosedUnitHeight = 50;

const short racePortraitHeight = 120;
const short racePortraitWidth = 100;

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
const short amountOfUnitTypes = 6;

const float backOfUToChooseSizeX = 300.f;
const float backOfUToChooseSizeY = 450.f;
const float backDescOfUnitsSizeX = 350.f;
const float backDescOfUnitsSizeY = windowHeight;
const float backUChosenSizeX = 300.f;
const float backUChosenSizeY = windowHeight;

const short amountOfNodUnits = 12;
const short amountOfGniUnits = 9;

const int leftMenuItemsYoffset = 160;

// DESCRIPTION MENU
const short descMenuWidth = 340;

// MAIN GAME

const std::string nodUnitsPaths[] = {
        "img/nod/attack_bike.png",
        "img/nod/militant.png",
        "img/nod/avatar.png",
        "img/nod/carryall.png",
        "img/nod/commando.png",
        "img/nod/fanatic.png",
        "img/nod/flame_tank.png",
        "img/nod/black_hand.png",
        "img/nod/shadow.png",
        "img/nod/scorp.png",
        "img/nod/saboteur.png",
        "img/nod/rocket.png"
};

const std::string gniUnitsPaths[] = {
        "img/gni/GDIrifle.png",
        "img/gni/GDImissile.png",
        "img/gni/GDIsniper.png",
        "img/gni/GDIgrenade.png",
        "img/gni/GDImamooth.png",
        "img/gni/GDIcolos.png",
        "img/gni/GDIcommando.png",
        "img/gni/GDIbmp.png",
        "img/gni/GDIjugg.png"};

const std::string playerPortraitPaths[] = {
        "img/players/playerPortrait1.png",
        "img/players/playerPortrait2.png"
};

// TODO: create LU of available units to choose of all races
// TODO: to emplace them in loop into vector of chosen units

enum nodUnits {
    attack_bike,
    militant,
    avatar,
    carryall,
    commando_slut,
    fanatic,
    flame_tank,
    black_hand,
    shadow,
    scorp,
    saboteur,
    rocket
};

enum gniUnits {
    rifle,
    missile,
    sniper,
    grenade,
    mamooth,
    colos,
    commando,
    bwp,
    juggernaut
};

#endif //_GAMECONSTANTS_H_
