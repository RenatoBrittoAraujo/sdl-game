#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "helpers.hpp"
#include "player.hpp"

#include <string>

namespace player_constants
{
    const float WALK_SPEED = 0.05f;
    const float GRAVITY = 0.0002f;
    const float GRAVITY_CAP = 0.8f;
}

Player::Player() {}

Player::Player(Graphics & graphics, float x, float y) :
    AnimatedSprite(graphics, "resources/char.png", 0, 0, 16, 16, x, y, 100),
    _dx(0),
    _dy(0),
    _facing(RIGHT),
    _grounded(false)
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
    if(this->_dy <= player_constants::GRAVITY_CAP)
    {
        this->_dy += player_constants::GRAVITY * elapsedTime;   
    }
    this->_x += this->_dx;
    this->_y += this->_dy;

    AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics & graphics)
{
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}

void Player::moveLeft()
{
    this->_dx = - player_constants::WALK_SPEED;
    this->playAnimation("RunLeft");
    this->_facing = LEFT;
}

void Player::moveRight()
{    
    this->_dx = player_constants::WALK_SPEED;
    this->playAnimation("RunRight");
    this->_facing = RIGHT;
}

void Player::stopMoving()
{
    this->_dx = 0.0f;
    this->playAnimation(this->_facing == LEFT ? "IdleLeft" : "IdleRight");
}

const float Player::getX() const 
{
    return this->_x;
}

const float Player::getY() const 
{
    return this->_x;
}

void Player::handleTileCollisions(std::vector<Rectangle> &others)
{
    
	for (int i = 0; i < others.size(); i++)
    {
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        
		if (collisionSide != sides::NONE)
        {
			switch (collisionSide) {
			case sides::TOP:
				this->_dy = 0;
				this->_y = others.at(i).getBottom() + 1;
				break;
			case sides::BOTTOM:
				this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
				this->_dy = 0;
				this->_grounded = true;
				break;
			case sides::LEFT:
				this->_x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			}

		}
    
	}
}