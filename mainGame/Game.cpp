//
// Created by Jebac Microsoft on 1/30/2018.
//
#include <algorithm>
#include "Game.h"
#include "stringHelper.h"
#include "loadFiles/load.inl"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
        : gameWindow(sf::VideoMode(1024, 768), "Warhammer_II", sf::Style::Close)
        , gameFont()
        , statisticsText()
        , statisticsUpdateTime()
        , statisticsNumFrames(0)
        , choosedUnit(nullptr)
        , framesToNextAttack(0)
        , mainGameMenu( &gameWindow, windowWidth, windowHeight )
        , choosingScreen( &gameWindow, windowWidth, windowHeight )
        , isInMainMenu(true)
        , isInChoosingScreen(false)
{
    gameWindow.setKeyRepeatEnabled(false);

    initLoad();

}

void Game::run()
{
    sf::Clock clock;
    sf::Clock mainClock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;


    while (gameWindow.isOpen())
    {
        //mainGameMenu.run();
        choosingScreen.run();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        mainTime = mainClock.getElapsedTime();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime, mainTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (gameWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonReleased:
                handlePlayerInputMouse( event.mouseButton.button, false );
                break;

            case sf::Event::Closed:
                gameWindow.close();
                break;
        }
    }
}

void Game::render()
{
    if( choosedUnit )
        std::cout << "true" << std::endl;
    else if( !choosedUnit )
        std::cout << "false" << std::endl;
    gameWindow.clear();
    gameWindow.setView(gameWindow.getDefaultView());

    if( choosedUnit )
    {
        choosedUnitBorder.setPosition( choosedUnit->getPortrait().getPosition() );
        gameWindow.draw(choosedUnitBorder);
    }
    for( auto& i : units ) {
        gameWindow.draw(i.getPortrait());
        gameWindow.draw(i.getPointRect());
        gameWindow.draw( i.getCombatChecker() );
    }
    for( auto& i : units )
    {
        gameWindow.draw( i.getHealthOutline() );
        gameWindow.draw( i.getHealthBar() );
    }

    gameWindow.draw(statisticsText);
    gameWindow.draw( statisticsMainGameTime );
    gameWindow.display();
}

void Game::updateStatistics(sf::Time _elapsedTime, sf::Time _mainTime)
{
    statisticsUpdateTime += _elapsedTime;
    statisticsNumFrames += 1;

    if (statisticsUpdateTime >= sf::seconds(1.0f))
    {
        statisticsText.setString(
                "Frames / Second = " + toString(statisticsNumFrames) + "\n" +
                "Time / Update = " + toString(statisticsUpdateTime.asMicroseconds() / statisticsNumFrames) + "us");

        statisticsUpdateTime -= sf::seconds(1.0f);
        statisticsNumFrames = 0;
    }
    statisticsMainGameTime.setString( "Main game time = " + toString( _mainTime.asMilliseconds() ) + "ms" );
    check_units_combat_status();
    units_fight();

}

/*++++++++++++++++++++++++++++++++++++
 *  COMBAT
 *
++++++++++++++++++++++++++++++++++++ */

bool Game::canEscapeFromCombat( const Unit* _entity )
{
        // check if unit can escape from combat in double move ( beacause of weak design )
        // in it's actual moving direction
        combatChecker.setPosition(_entity->getPortrait().getPosition().x + _entity->getEscapeDeltas().x * unitHeight / 4,
                                  _entity->getPortrait().getPosition().y + _entity->getEscapeDeltas().y * unitWidth / 4);

        for (const auto& unitToCheck : units)
        {
            if (&unitToCheck == _entity)
            {
                ; // skip, it's unit we are checking for, it will always collide with itself
            }
            else
            {
                if (combatChecker.getGlobalBounds().intersects(unitToCheck.getPortrait().getGlobalBounds()))
                {
                    return false;
                }
            }
        }
    return true;
}

sf::Vector2f Game::getUnitCombatDirection( const Unit* _attacker, const Unit* _target )
{
    float deltaX = _target->getPortrait().getPosition().x - _attacker->getPortrait().getPosition().x;
    float deltaY = _target->getPortrait().getPosition().y - _attacker->getPortrait().getPosition().y;
    float length = static_cast<float>( sqrt( ( pow( deltaX, 2 ) + pow( deltaY, 2 ) ) ) );
    sf::Vector2f retVector( deltaX/length, deltaY/length );
    return retVector;
}

bool Game::unitsAreInCombat( const Unit* _attacker, const Unit* _target )
{
    // checking happened for same unit
    if( _attacker == _target )
    {
        return false;
    }

    sf::Vector2f attackMove( getUnitCombatDirection( _attacker, _target ) );
    combatChecker.setPosition( _attacker->getPortrait().getPosition().x + attackMove.x * unitHeight/4 ,
                               _attacker->getPortrait().getPosition().y + attackMove.y * unitWidth/4);

    // old diagnostic to watch collision checkers
    //gameWindow.display();
   // gameWindow.draw( combatChecker );

    if( combatChecker.getGlobalBounds().intersects( _target->getPortrait().getGlobalBounds() ) )
    {
        return true;
    }
    return false;
}

void Game::unitsEnterCombat( Unit* _attacker, Unit* _defender )
{
    _attacker->enterCombat( _defender );
    _defender->enterCombat( _attacker);
}

bool Game::unitCanMove( Unit* _entity )
{
    combatChecker.setPosition( _entity->getPortrait().getPosition().x + _entity->getDeltas().x * unitHeight/3,
                               _entity->getPortrait().getPosition().y + _entity->getDeltas().y * unitWidth/3 );
    for( auto& i : units )
    {
        if( i.getPortrait().getGlobalBounds().intersects( combatChecker.getGlobalBounds() ) )
        {
            if( &i == _entity )
            {
                // do nothing, it's unit we are checking for
            }
            else
            {

                return false;
            }
        }
        return true;

    }
}

void Game::check_units_combat_status() {
    // clearing vector from enemies from previous frame
    // primitive and inefficient way, but for now its working
    for (auto &i : units)
    {
        i.clearEnemiesVector();
    }

    // TODO: finish new logic
    // TODO: checking combat before iterating
    // TODO: remove switch combat state from other places

    // main if to check if therre is anybody to fight with
    if (units.size() > 1)
    {
        for (auto &unit : units) {
            for (auto &enemy : units) {
                if (unitsAreInCombat(&unit, &enemy))
                {
                        unitsEnterCombat(&unit, &enemy);
                }
            }
        }
    }
}

void Game::units_fight()
{
    int j=0; // int for output
    bool resetFramesToNextAttack = false;
    ++framesToNextAttack;
    if( framesToNextAttack == 650 )
    {
        resetFramesToNextAttack = true;
    }
    for( auto& i : units )
    {
            if( resetFramesToNextAttack )
            {
                i.fight();
            }
        ++j;
    }
    if( resetFramesToNextAttack )
        framesToNextAttack = 0;

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

}

void Game::handlePlayerInputMouse(sf::Mouse::Button button, bool isPressed )
{
    if( button == sf::Mouse::Button::Right)
    {
        sf::Vector2f pos = sf::Vector2f( static_cast<float>(sf::Mouse::getPosition(gameWindow).x), static_cast<float>(sf::Mouse::getPosition(gameWindow).y) );
        for( auto& i : units )
        {
                if (i.getPortrait().getGlobalBounds().contains(pos.x, pos.y))
                {
                    std::cout << "unit choosed" << std::endl;
                    choosedUnitBorder.setPosition(i.getPortrait().getPosition());
                    i.selectOn();
                    choosedUnit = &i;
                    return;
                }   else
                {
                    if (i.isSelected())
                         i.selectOff();
                }
        }
        if( choosedUnit )
        {
            std::cout << "POINT CHOOSED" << std::endl;
            choosedUnit->setMovingPoint( pos );
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    for( int i=0; i<units.size(); ++i )
    {

        if( units[i].getHP() <= 0 )
        {
            if( choosedUnit == &units[i] )
            {
                choosedUnit = nullptr;
            }
        }
    }

    units.erase( std::remove_if( units.begin(), units.end(),
                                 []( Unit& _un ){ return (_un.getHP() <= 0); }),
                 units.end() );

    for( auto& i : units )
    {
        if( i.combatStatus() && canEscapeFromCombat( &i ) )
        {
            i.setDeltas( i.getEscapeDeltas() );
            //std::cout << i.getNamePtr() << " escaped" << std::endl;
            for( int moveIter=0; moveIter<10; ++moveIter )
            {
                i.move();
            }
        }
        else
        {
            i.move();
        }
        i.exitCombat();
    }

}