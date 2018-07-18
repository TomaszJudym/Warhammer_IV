//
// Created by Jebac Microsoft on 2/11/2018.
//
#define MOVING_DEBUG 0

#include "unitAdds.inl"
#include "Unit.h"
#include <cmath>
const float Unit::unitSpeed = 1.5;

Unit::Unit():
healthBar(0){
}

Unit::Unit( sf::Sprite& _portrait,
char* _name,
int _hp,
float _fp,
short _team ) :
         name(_name)
        ,hp(_hp)
        ,firepower(_fp)
        ,selected(false)
        ,outOfBorder(false)
        ,inCombat(false)
        ,escapesFromCombat(false)
       // ,enemy(nullptr)
        ,enemies()
        ,escape(goingOut::up)
        ,currentState(stopped)
        ,portrait(_portrait)
        ,team(_team)
        ,point(_portrait.getPosition().x, _portrait.getPosition().y )
        ,pointRect( sf::Vector2f( 4.0, 4.0 ) )
        ,combatChecker( sf::Vector2f( unitWidth, unitHeight ) )
        ,healthBar( _hp )
{
    initLoad();
}
/* SIGSEGV : <
Unit::Unit( const Unit& _another ) :
healthBar( _another.healthBar )
{
    strcpy( _another.name, getNamePtr() );
    hp = _another.hp;
    firepower = _another.firepower;
    team = _another.team;
    selected = _another.selected;
    outOfBorder = _another.outOfBorder;
    inCombat = _another.inCombat;
    escapesFromCombat = _another.escapesFromCombat;
    enemies = _another.enemies;
    escape = _another.escape;
    currentState = _another.currentState;
    portrait = _another.portrait;
    team = _another.team;
    point = _another.point;
    pointRect = _another.pointRect;
    combatChecker = _another.combatChecker;
    healthBar = _another.healthBar;
}
 */


void Unit::selectOff() { selected = false; }
void Unit::selectOn() { selected = true; }
bool Unit::isSelected() { return selected; }

void Unit::setTeam( bool _team ){
    team = _team;
}

bool Unit::getTeam() const{
    return team;
}


/* +++++++++++++++++++++++++++++++++++++++++++++++
 *
 * COMBAT
 *
 +++++++++++++++++++++++++++++++++++++++++++++++*/

void Unit::clearEnemiesVector()
{
    enemies.clear();
}

void Unit::enterCombat(Unit* _against)
{
    move(); move();
    if( deltas.x != 0.f && deltas.y != 0.f ) {

        deltasToEscape = deltas;
    }
    inCombat = true;
    deltas.x = 0.f;
    deltas.y = 0.f;
    bool enemyAlreadyEncountered = false;
    if( !enemies.empty() )
    {
        for (const auto &i : enemies) {
            if (&(*i) == _against)
            {
                enemyAlreadyEncountered = true;
                break;
            }
        }
    }
    if( !enemyAlreadyEncountered )
    {
        enemies.push_back( _against );
    }
}

void Unit::exitCombat()
{
    //enemy = nullptr;
    inCombat = false;

}
void Unit::fight()
{
    for( auto& i : enemies )
    {
        i->changeHp(firepower);
    }
}
void Unit::changeHp( float _delta )
{
    if( (hp - _delta) > 0 )
    {
        hp -= _delta;
        healthBar.decrease(_delta);
    }
    if( (hp - _delta) <= 0 )
    {
        std::cout << "unit " << getNamePtr() << " died" << std::endl;
        hp = 0;
        healthBar.decrease(_delta);
    }
}
void Unit::die()
{
    delete this;
}
/**++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * MOVING
 *
 ++++++++++++++++++++++++++++++++++++++++++++++++++*/


void Unit::setMovingPoint( float _x, float _y )
{
    point.x = _x; point.y = _y;
    float actualX = portrait.getPosition().x;
    float actualY = portrait.getPosition().y;
    deltas.x = 1.0;
    deltas.y = actualX / actualY;
    pointRect.setPosition( _x, _y );
}

void Unit::setMovingPoint( sf::Vector2f& _xy )
{
    point = _xy;
    sf::Vector2f position = portrait.getPosition();
    // deltas calculated by sustraction destination from source
    float dx = point.x - position.x;
    float dy = point.y - position.y;                            // ->
    // normalizing vector by dividing deltas by its vectors value |v|
    auto length = static_cast<float>(sqrt( (dx * dx) + (dy * dy) ));
    deltas.x = dx / length;
    deltas.y = dy / length;
    pointRect.setPosition( _xy );
}

bool Unit::moveAtBorder()
{
    if( deltas.y == 0.f ){
        if( escape == up ){
            if( enterBorderPoint.x >= point.x ){
                if( portrait.getPosition().x <= point.x )
                {
                    deltas.x = 0.f;
                    return true;
                }
            }
            if( enterBorderPoint.x < point.x )
            {
                if( portrait.getPosition().x >= point.x )
                {
                    deltas.x = 0.f;
                    return true;
                }
            }
        }
        if( escape == down ) {
            if( enterBorderPoint.x >= point.x ){
                if( portrait.getPosition().x <= point.x )
                {
                    deltas.x = 0.f;
                    return true;
                }
            }
            if( enterBorderPoint.x < point.x )
            {
                if( portrait.getPosition().x >= point.x )
                {
                    deltas.x = 0.f;
                    return true;
                }
            }
        }
    }
    if( deltas.x == 0.f ){
        if( escape == left ) {
            if( enterBorderPoint.y >= point.y )
            {
                if( portrait.getPosition().y <= point.y ){
                    deltas.y = 0.f;
                    return true;
                }
            }
            if( enterBorderPoint.y < point.y ){
                if( portrait.getPosition().y >= point.y ){
                    deltas.y = 0.f;
                    return true;
                }
            }
        }
        if( escape == right ) {
            if( enterBorderPoint.y >= point.y )
            {
                if( portrait.getPosition().y <= point.y ){
                    deltas.y = 0.f;
                    return true;
                }
            }
            if( enterBorderPoint.y < point.y ){
                if( portrait.getPosition().y >= point.y ){
                    deltas.y = 0.f;
                    return true;
                }
            }
        }
    }
    portrait.move( deltas.x, deltas.y );
    healthBar.move( deltas.x, deltas.y );
    return false;
}

void Unit::move()
{
    state actualState = checkState();
    if( actualState == combat )
    {   if( MOVING_DEBUG )
            std::cout << "combat" << std::endl;
    }
    if( actualState == borderEscape )
    {   if( MOVING_DEBUG  )
         std::cout << "borderEscape: " << deltas.y << std::endl;
        moveAtBorder();
    }
    if( actualState == stopped )
    {   if( MOVING_DEBUG  )
            std::cout << "stopped" << std::endl;
        deltas.x = deltas.y = 0.f;
    }
    if( actualState == moving )
    {
        if( MOVING_DEBUG  )
            std::cout << "moving" << std::endl;
        portrait.move(deltas.x, deltas.y);
        healthBar.move( deltas.x, deltas.y );
    }


}

Unit::state Unit::checkState()
{
    if( inCombat )
    {
        return combat;
    }
    if( checkBorders() ) {
        return borderEscape;
    }
    if( pointRect.getGlobalBounds().contains( portrait.getPosition() ) ) {
        return stopped;
    }
    return moving;
}

bool Unit::checkBorders() {
    // right`
    if( deltas.x != 0.f && deltas.y != 0.f ) {
        borderDeltas = deltas;
        enterBorderPoint = portrait.getPosition();
    }
    if( ( portrait.getPosition().x + unitWidth / 2 + borderDeltas.x ) >= windowWidth) {
        escape = right;
        outOfBorder = true;
        deltas.x = 0.f;
        return true;
    }
    if( ( portrait.getPosition().x - unitWidth/2 + borderDeltas.x ) <= 0 ) { // left
        escape = left;
        outOfBorder = true;
        deltas.x = 0.f;
        return true;
    }
    if( ( portrait.getPosition().y + unitHeight/2 + borderDeltas.y ) >= windowHeight ) { // down
        escape = down;
        outOfBorder = true;
        deltas.y = 0.f;
        return true;
    }
    if( ( portrait.getPosition().y - unitHeight/2 + borderDeltas.y )  <= 0 ) { // up
        escape = up;
        outOfBorder = true;
        deltas.y = 0.f;
        return true;
    }
    outOfBorder = false;
    return false;
}


/*+ + + + + + + + + + + + + + + + + + + + +
 *
 * OPERATORS
 *
 + + + + + + + + + + + + + + + + + + + + + */




Unit& Unit::operator=( const Unit& _unit )
{
    std::cout << "copy assignment operator used" << std::endl;
    if (this == &_unit) {
        return *this;
    }
    else {
        const char* newName = _unit.getNamePtr();
        size_t newNameSize = 0;
        while( *(newName+newNameSize) != '\0' )
        {
            ++newNameSize;
        }
        name = new char[newNameSize+1];
        std::memcpy( name, _unit.getNamePtr(), newNameSize );
        name[newNameSize] = '\0';
        hp = _unit.hp;
        firepower = _unit.firepower;
        //portrait.setPosition(_unit.getPortrait().getPosition().x, _unit.getPortrait().getPosition().y );
        portrait.setTexture(*(_unit.portrait.getTexture()));
        selected = _unit.selected;
        outOfBorder = _unit.outOfBorder;
        inCombat = _unit.inCombat;
        escapesFromCombat = _unit.escapesFromCombat;
        team = _unit.team;
        deltas = _unit.deltas;
        deltasToEscape = _unit.deltasToEscape;
        borderDeltas = _unit.borderDeltas;
        point = _unit.point;
        enterBorderPoint.x = _unit.enterBorderPoint.x;
        enterBorderPoint.y = _unit.enterBorderPoint.y;
        pointRect = _unit.pointRect;
        combatChecker = _unit.pointRect;
        escape = _unit.escape;
        currentState = _unit.currentState;
        healthBar = _unit.healthBar;
        enemies = _unit.enemies;
        portrait.setPosition( _unit.getPortrait().getPosition().x,
                              _unit.getPortrait().getPosition().y);healthBar.setPosition(
                sf::Vector2f( portrait.getPosition().x,
                              portrait.getPosition().y - healthBarYfit ) );
        healthBar.setPosition( sf::Vector2f(
                        portrait.getPosition().x-(unitWidth/2),
                        portrait.getPosition().y - healthBarYfit)
        );


    }
}

/*+ + + + + + + + + + + + + + + + + + + + +
 *
 * SETTERS
 *
 + + + + + + + + + + + + + + + + + + + + + */

void Unit::setDeltas( sf::Vector2f _newDeltas )
{
    deltas = _newDeltas;
}

void Unit::setDeltas( float _x, float _y )
{
    deltas.x = _x;
    deltas.y = _y;
}

/*+ + + + + + + + + + + + + + + + + + + + +
 *
 * GETTERS
 *
 + + + + + + + + + + + + + + + + + + + + + */
char* Unit::getNamePtr() const
{
    char* retPtr = name;
    return name;
}

HealthBar& Unit::getMainHealthBar()
{
    return healthBar;
}

sf::RectangleShape& Unit::getHealthBar()
{
    return healthBar.getBar();
}

sf::RectangleShape& Unit::getHealthOutline()
{
    return healthBar.getOutline();
}

sf::Vector2f& Unit::getPoint()
{
    return point;
}

const sf::Vector2f& Unit::getDeltas() const
{
    return deltas;
}

const sf::Vector2f Unit::getEscapeDeltas() const
{
    return deltasToEscape;
}

sf::Sprite& Unit::getPortrait()
{
    return portrait;
}

sf::Sprite Unit::getPortrait() const
{
    return portrait;
}

sf::RectangleShape& Unit::getPointRect()
{
    return pointRect;
}

sf::RectangleShape& Unit::getCombatChecker()
{
    return combatChecker;
}

HealthBar Unit::getMainHealthBar() const
{
    return healthBar;
}

short Unit::getHP()
{
    return hp;
}

bool& Unit::combatStatus()
{
    return inCombat;
}


Unit::~Unit()
{
   // enemy = nullptr;
}

