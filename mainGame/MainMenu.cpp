//
// Created by Ackan on 21.05.2018.
//

#include "MainMenu.h"

void MainMenu::initLoad()
{
    // attempt to load font file
    if( !mainMenuFont.loadFromFile( "font/Consolas.ttf" ) )
    {
        std::cout << "Error loading font file font/Consolas.ttf" << std::endl;
    }

    //setting fonts for all text objects in main menu
    start.setFont( mainMenuFont );
    options.setFont( mainMenuFont );
    for( auto iter = std::begin( insideOptions ); iter != std::end( insideOptions ); ++iter )
    {
        iter->setFont( mainMenuFont );
    }
    back.setFont( mainMenuFont );
    exit.setFont( mainMenuFont );
    for( int i=0; i<3; ++i )
    {
        insideOptionsVideo[i].setFont( mainMenuFont );
        insideOptionsSound[i].setFont( mainMenuFont );
        insideOptionsInput[i].setFont( mainMenuFont );
    }


    // setting strings for text objects
    start.setString( "Start" );
    options.setString( "Options" );
    insideOptions[0].setString( "Video" );
    insideOptions[1].setString( "Audio" );
    insideOptions[2].setString( "Input" );
    // SOUND
    insideOptionsSound[0].setString( "Main Volume" );
    insideOptionsSound[1].setString( "Combat Volume" );
    insideOptionsSound[2].setString( "Effects Volume" );
    // VIDEO
    insideOptionsVideo[0].setString( "Resolution" );
    insideOptionsVideo[1].setString( "Gamma" );
    insideOptionsVideo[2].setString( "Brightness" );
    // INPUT
    insideOptionsInput[0].setString( "Mouse" );
    insideOptionsInput[1].setString( "Keyboard" );
    insideOptionsInput[2].setString( "Advanced" );
    back.setString( "Back" );
    exit.setString( "Exit" );

    start.setOrigin( mainMenuScaleVec.x/2, mainMenuScaleVec.y/2 );
    options.setOrigin( mainMenuScaleVec.x/2, mainMenuScaleVec.y/2  );
    for( auto iter = std::begin( insideOptions ); iter != std::end( insideOptions ); ++iter )
    {
        iter->setOrigin( mainMenuScaleVec.x/2, mainMenuScaleVec.y/2 );
    }
    back.setOrigin( mainMenuScaleVec.x/2, mainMenuScaleVec.y/2  );
    exit.setOrigin( mainMenuScaleVec.x/2, mainMenuScaleVec.y/2 );

    //setting origins of texts in inner menus
    for( int i=0; i<amountOfTextIconsInOptionsSoundMenu; ++i ) // also in other sumenus
    {
        std::cout << "height: " << insideOptionsInput[i].getGlobalBounds().width/2 << std::endl;
        insideOptionsSound[i].setOrigin( insideOptionsSound[i].getGlobalBounds().width/2, mainMenuScaleVec.y/2  );
        insideOptionsVideo[i].setOrigin( insideOptionsVideo[i].getGlobalBounds().width/2, mainMenuScaleVec.y/2 );
        insideOptionsInput[i].setOrigin( insideOptionsInput[i].getGlobalBounds().width/2, mainMenuScaleVec.y/2 );
    }

    // setting color for text objects in main menu
    start.setFillColor( sf::Color::Magenta );
    options.setFillColor( sf::Color::Magenta );
    for( int i = 0; i < 3; ++i )
    {
        insideOptions[i].setFillColor( sf::Color::Magenta );
        insideOptionsSound[i].setFillColor( sf::Color::Magenta );
        insideOptionsVideo[i].setFillColor( sf::Color::Magenta );
        insideOptionsInput[i].setFillColor( sf::Color::Magenta );
    }
    back.setFillColor( sf::Color::Magenta );
    exit.setFillColor( sf::Color::Magenta );

    // filling ptr tab with addresses of text objects in main menu
    textsInMainMenu[0] = &start;
    textsInMainMenu[1] = &options;
    textsInMainMenu[2] = &back;
    textsInMainMenu[3] = &exit;
    // SOUND MENU TEXT
    for( int i=0; i<3; ++i )
    {
        textsInOptionsSoundMenu[i] = &insideOptionsSound[i];
        textsInOptionsVideoMenu[i] = &insideOptionsVideo[i];
        textsInOptionsInputMenu[i] = &insideOptionsInput[i];
    }
    textsInOptionsSoundMenu[3] = &back;
    textsInOptionsVideoMenu[3] = &back;
    textsInOptionsInputMenu[3] = &back;

    // VIDEO MENU TEXT

    // filling ptr tab with addresses of text objects in options menu
    for( int i=0; i<3; ++i )
    {
        textsInOptionsMenu[i] = &insideOptions[i];
    }
    // including back button, same like in other submenus
    textsInOptionsMenu[3] = &back;


    // setting positions of text objects in main menu
    start.setPosition( windowWidth/2, 100.f );
    options.setPosition( windowWidth/2, 200.f );
    exit.setPosition( windowWidth/2, 300.f );
    for( int i=0; i<3; ++i )
    {
        insideOptions[i].setPosition( windowWidth/2, (i+1)*100.f );
        insideOptionsSound[i].setPosition( windowWidth/2, (i+1)*100.f );
        insideOptionsVideo[i].setPosition( windowWidth/2, (i+1)*100.f );
        insideOptionsInput[i].setPosition( windowWidth/2, (i+1)*100.f );
    }
    back.setPosition( 400.f, 400.f );


}

MainMenu::MainMenu( sf::RenderWindow* _winPtr, int _width, int _height )
: width(_width)
, height(_height)
, gameWindowPtr(_winPtr)
, isActive(true)
, inOptions(false)
, inOptionsInput(false)
, inOptionsVideo(false)
, inOptionsSound(false)
, actualGameState( MAIN_MENU )
{
    initLoad();
}

sf::RenderWindow* MainMenu::getWindowPtr()
{
    return gameWindowPtr;
}

void MainMenu::handlePlayerInputMouse( sf::Mouse::Button _button, bool _isPressed )
{
    sf::Vector2f mousePos = sf::Vector2f( ( sf::Mouse::getPosition( *gameWindowPtr ) ) );
    if( _button == sf::Mouse::Button::Left )    // left button pressed
    {

        if( actualGameState == MAIN_MENU )    // user is in main menu
        {
            if (start.getGlobalBounds().contains(mousePos))
            {
                actualGameState = MAIN_GAME;
                end();
            }
            if (options.getGlobalBounds().contains(mousePos))
            {
                actualGameState = OPTIONS_MENU;
            }
            if (exit.getGlobalBounds().contains(mousePos))
            {
                std::cout << "process finished by user with code 0" << std::endl;
                std::exit(0);
            }
        }
        else if( actualGameState == OPTIONS_MENU )    // user is inside inner options menu
        {

            if( insideOptions[0].getGlobalBounds().contains( mousePos ) ) // video
            {
                actualGameState = OPTIONS_VIDEO_MENU;
            }
            if( insideOptions[1].getGlobalBounds().contains( mousePos ) ) // audio
            {
                actualGameState = OPTIONS_SOUND_MENU;
            }
            if( insideOptions[2].getGlobalBounds().contains( mousePos ) ) // input
            {
                actualGameState = OPTIONS_INPUT_MENU;
            }
            if( back.getGlobalBounds().contains( mousePos ) ) // exit inner options menu
            {
                actualGameState = MAIN_MENU;
            }
        }
        else if ( actualGameState == OPTIONS_VIDEO_MENU)
        {
            if (back.getGlobalBounds().contains(mousePos)) {
                actualGameState = OPTIONS_MENU;
            }
        }
        else if ( actualGameState == OPTIONS_SOUND_MENU)
        {
            if (back.getGlobalBounds().contains(mousePos)) {
                actualGameState = OPTIONS_MENU;
            }
        }
        else if ( actualGameState == OPTIONS_INPUT_MENU)
        {
            if (back.getGlobalBounds().contains(mousePos)) {
                actualGameState = OPTIONS_MENU;
            }
        }

    }
}

void MainMenu::processEvents()
{
    sf::Event event;
    while (gameWindowPtr->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::MouseButtonReleased:
                handlePlayerInputMouse( event.mouseButton.button, true );
                break;

            case sf::Event::Closed:
                gameWindowPtr->close();
                break;
        }
    }
}

void MainMenu::colorText()
{
    sf::Vector2f mousePos = sf::Vector2f( ( sf::Mouse::getPosition( *gameWindowPtr ) ) );
    // checking if we need to color anything
    if( actualGameState == MAIN_MENU )
    {
        if (start.getGlobalBounds().contains(mousePos)) {
            start.setFillColor(sf::Color::Cyan);
        } else if (start.getFillColor() != sf::Color::Magenta) {
            start.setFillColor(sf::Color::Magenta);
        }
        if (options.getGlobalBounds().contains(mousePos)) {
            options.setFillColor(sf::Color::Cyan);
        } else if (options.getFillColor() != sf::Color::Magenta) {
            options.setFillColor(sf::Color::Magenta);
        }
        if (exit.getGlobalBounds().contains(mousePos)) {
            exit.setFillColor(sf::Color::Cyan);
        } else if (exit.getFillColor() != sf::Color::Magenta) {
            exit.setFillColor(sf::Color::Magenta);
        }
    }
    else if( actualGameState == OPTIONS_MENU ) // options menu
    {
        for( auto i : textsInOptionsMenu )
        {
            if (i->getGlobalBounds().contains(mousePos)) {
                i->setFillColor(sf::Color::Cyan);
            } else if (i->getFillColor() != sf::Color::Magenta) {
                i->setFillColor(sf::Color::Magenta);
            }
        }
    }
    else if( isInInnerOptions() )
    {
        sf::Text **subOptionsToColor;
        if (actualGameState == OPTIONS_SOUND_MENU)
            subOptionsToColor = textsInOptionsSoundMenu;
        if (actualGameState == OPTIONS_VIDEO_MENU)
            subOptionsToColor = textsInOptionsVideoMenu;
        if (actualGameState == OPTIONS_INPUT_MENU)
            subOptionsToColor = textsInOptionsInputMenu;

        for (int i = 0; i < 3; ++i)
        {
            if (subOptionsToColor[i]->getGlobalBounds().contains(mousePos))
            {
                if ( (*(subOptionsToColor+i))->getFillColor() == sf::Color::Magenta)
                {
                    subOptionsToColor[i]->setFillColor(sf::Color::Cyan);

                }
            }
            else if( subOptionsToColor[i]->getFillColor() != sf::Color::Magenta )
            {
                subOptionsToColor[i]->setFillColor(sf::Color::Magenta);
            }
        }
    }

    if (back.getGlobalBounds().contains(mousePos))
    {
        if( back.getFillColor() == sf::Color::Magenta )
            back.setFillColor(sf::Color::Cyan);
    }
    else if( back.getFillColor() != sf::Color::Magenta )
    {
        back.setFillColor( sf::Color::Magenta );
    }

}




void MainMenu::run()
{
    while (gameWindowPtr->isOpen() && isActive)
    {
        processEvents();
        render();
    }
}


// checking if player is in submenu options: sound, video, input
inline bool MainMenu::isInInnerOptions()
{
    return ( actualGameState == OPTIONS_SOUND_MENU ||
             actualGameState == OPTIONS_VIDEO_MENU ||
             actualGameState == OPTIONS_INPUT_MENU );
}

//################## RENDERERS

void MainMenu::renderMainMenu()
{
    gameWindowPtr->draw( start );
    gameWindowPtr->draw( options );
    gameWindowPtr->draw( exit );
}

void MainMenu::renderOptionsMenu()
{
    for( int i=0; i < amountOfTextIconsInOptionsMenu; ++i )
    {
        gameWindowPtr->draw( insideOptions[i] );
    }
    gameWindowPtr->draw(back);
}
void MainMenu::renderSound()
{
    for( int i=0; i < amountOfTextIconsInOptionsSoundMenu; ++i )
    {
        gameWindowPtr->draw( insideOptionsSound[i] );
    }
    gameWindowPtr->draw(back);
}

void MainMenu::renderVideo()
{
    for( int i=0; i<amountOfTextIconInOptionsVideoMenu; ++i )
    {
        gameWindowPtr->draw( insideOptionsVideo[i] );
    }
    gameWindowPtr->draw(back);
}

void MainMenu::renderInput()
{
    for( int i=0; i<amountOfTextIconsInOptionsInputMenu; ++i )
    {
        gameWindowPtr->draw( insideOptionsInput[i] );
    }
    gameWindowPtr->draw(back);
}

//######################## MAIN RENDERER ########################
void MainMenu::render() {
    //showGamestate();
    // clear screen from previous frame
    gameWindowPtr->clear(sf::Color::Black);
    if (actualGameState == MAIN_MENU) // in main manu with start, options and exit
    {
        renderMainMenu();
    } else if (actualGameState == OPTIONS_MENU) // inside inner options with video, sound and input methods
    {
        renderOptionsMenu();
    } else if (actualGameState == OPTIONS_SOUND_MENU) {
        renderSound();
    } else if (actualGameState == OPTIONS_VIDEO_MENU) {
        renderVideo();
    } else if (actualGameState == OPTIONS_INPUT_MENU) {
        renderInput();
    }
    colorText();
    gameWindowPtr->display();

}

void MainMenu::turnOn()
{
    isActive = true;
}


void MainMenu::end()
{
    isActive = false;
}
//#################

//TODO: InsideOptions arrays are not initialized, so pointers
//TODO: are pointing to nothing, initialize them in initLoad() method