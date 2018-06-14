//
// Created by Ackan on 21.05.2018.
//

#include <SFML/System.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#include <iostream>

#include "gameConstants.h"

#ifndef _MAINMENU_H
#define _MAINMENU_H

// putting this vector inside gameConstants caused linker errors after 100% linking completion,
// looked like stack of broken includes, still not figured out why, probably something to do
// with sf namespace and sfml library itself, other consts were working fine
const sf::Vector2f mainMenuScaleVec( 100.f, 50.f );

class MainMenu {
private:
    // enum with render scenes states in gameConstants.h
    GAME_STATE actualGameState;
    const int width;
    const int height;
    sf::RenderWindow* gameWindowPtr;
    sf::Font mainMenuFont;

    // main menu texts
    sf::Text start;
    sf::Text options;
    sf::Text exit;
    sf::Text back;

    sf::Text insideOptions[3];
    // video
    // audio
    // input

    sf::Text insideOptionsSound[4];
    // main
    // combat
    // effects

    sf::Text insideOptionsVideo[4];
    // resolution
    // gamma
    // brightness

    sf::Text insideOptionsInput[4];
    // mouse
    // keyboard
    // advanced

    // for easier iteration through all text objects in menus
    sf::Text* textsInMainMenu[amountOfTextIconsInMainMenu];
    sf::Text* textsInOptionsMenu[amountOfTextIconsInOptionsMenu];
    sf::Text* textsInOptionsSoundMenu[amountOfTextIconsInOptionsSoundMenu];
    sf::Text* textsInOptionsVideoMenu[amountOfTextIconInOptionsVideoMenu];
    sf::Text* textsInOptionsInputMenu[amountOfTextIconsInOptionsInputMenu];
    bool isActive;
    // is user inside options menu
    bool inOptions;
    bool inOptionsSound;
    bool inOptionsVideo;
    bool inOptionsInput;
    bool isInInnerOptions();
    void initLoad();
public:
    explicit MainMenu( sf::RenderWindow* _winPtr, int _width, int _height );
    sf::RenderWindow* getWindowPtr();

    void colorText();
    void processEvents();
    //################ RENDER
    void render();
    void renderMainMenu();
    void renderOptionsMenu();
    void renderSound();
    void renderVideo();
    void renderInput();
    //################
    void run();
    void handlePlayerInputMouse(sf::Mouse::Button button, bool isPressed);
    void turnOn();
    void end();
};


#endif //_MAINMENU_H
