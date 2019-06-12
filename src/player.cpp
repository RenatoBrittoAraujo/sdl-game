#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "player.hpp"

#include <string>

namespace player_contants
{
    const float WALK_SPEED = 0.1f;
}

Player::Player() {}

Player::Player(Graphics & graphics, float x, float y) :
    AnimatedSprite(graphics, "resources/char.png", 0, 0, 16, 16, x, y, 100)
{
    graphics.loadImage("resources/char.png");
    this->setupAnimation();
    this->playAnimation("RunRight");
}

void Player::setupAnimation()
{   
    this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0,0));
    this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0,0));
    this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0,0));
    this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0,0));
}

void Player::animationDone(std::string currentAnimation)
{
    
}

void Player::update(float elapsedTime)
{
    this->_x += this->_dx;
    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics & graphics)
{
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}

void Player::moveLeft()
{
    this->_dx = - player_contants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->_facing = LEFT;
}

void Player::moveRight()
{    
    this->_dx = player_contants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->_facing = RIGHT;
}

void Player::stopMoving()
{
    this->_dx = 0.0f;
    this->playAnimation(this->_facing == LEFT ? "IdleLeft" : "IdleRight");
}



