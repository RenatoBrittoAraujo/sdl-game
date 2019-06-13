#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "player.hpp"
#include "slopes.hpp"

#include <string>

namespace player_constants
{
    const float WALK_SPEED = 0.6f;
    const float GRAVITY = 0.009f;
    const float GRAVITY_CAP = 5.0f;
    const float JUMP_SPEED = 1.8f;
}

Player::Player() {}

Player::Player(Graphics & graphics, Vector2 spawnPoint) :
    AnimatedSprite(graphics, "resources/char.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
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

void Player::handleTileCollisions(std::vector<Rectangle> & collisionRects)
{
	for(auto rectangle : collisionRects)
    {
		sides::Side collisionSide = Sprite::getCollisionSide(rectangle);

        switch (collisionSide) {
        case sides::TOP:
            this->_dy = 0;
            this->_y = rectangle.getBottom() + 1;
            if(this->_grounded)
            {
                this->_dx = 0;
                this->_x -= this->_facing == RIGHT ? 1.0f : -1.0f;
            }
            break;
        case sides::BOTTOM:
            this->_y = rectangle.getTop() - this->_boundingBox.getHeight() - 1;
            this->_dy = 0;
            this->_grounded = true;
            break;
        case sides::LEFT:
            this->_x = rectangle.getRight() + 1;
            break;
        case sides::RIGHT:
            this->_x = rectangle.getLeft() - this->_boundingBox.getWidth() - 1;
            break;
        default:
            throw "Invalid collision type | Class: player";
            break;
		}
	}
}

void Player::handleSlopeCollisions(std::vector<Slope> & slopes)
{
    for(Slope & slope : slopes)
    {
        if(!slope.collidesWith(this->getBoundingBox()))
            continue;
        int b = (slope.getP1().y - (slope.getSlope() * fabs(slope.getP1().x)));
        int centerX = this->_boundingBox.getCenterX();

        // This magic number fixes incorrect calculations on slope collisions and is to be removed

        int newY = (slope.getSlope() * centerX) + b - 8;
        if(this->_grounded)
        {
            this->_y = newY - this->_boundingBox.getHeight();
        }
    }
}

void Player::jump()
{
    if(this->_grounded)
    {
        this->_dy = -player_constants::JUMP_SPEED;
        this->_grounded = false;
    }
}