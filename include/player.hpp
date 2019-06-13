#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.hpp"
#include "slopes.hpp"
#include "rectangle.hpp"

class Graphics;


class Player : public AnimatedSprite
{
public:
    Player();
    Player(Graphics & graphics, Vector2 spawnPoint);
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimation();

    void moveLeft();
    void moveRight();
    void stopMoving();

    const float getX() const;
    const float getY() const;

    void handleTileCollisions(std::vector<Rectangle> & tiles);
    void handleSlopeCollisions(std::vector<Slope> & slopes);

    void jump();

private:

    float _dx, _dy;
    Direction _facing;

    bool _grounded;
};

#endif