//
// Created by Ackan on 02.07.2018.
//

#ifndef WARHAMMER_II_BETTERCHOOSINGSCREEN_H
#define WARHAMMER_II_BETTERCHOOSINGSCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>
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

class betterChoosingScreen {

    sf::RenderWindow* winPtr;
    const int width;
    const int height;


    void initLoad();

public:
    explicit betterChoosingScreen( sf::RenderWindow* _winPtr, int _width, int _height );
    void handleInputMouseScroll( float _scrollDelta );
    void handleInputMouse( sf::Mouse::Button _released );
    void processEvents();
    void run();
    void render();

};


#endif //WARHAMMER_II_BETTERCHOOSINGSCREEN_H
