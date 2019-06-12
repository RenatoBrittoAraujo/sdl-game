#ifndef PLAYER_H
#define PLAYER_H

#include "animatedSprite.hpp"
class Graphics;


class Player : public AnimatedSprite
{
public:
    Player();
    Player(Graphics & graphics, float x, float y);
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimation();

    void moveLeft();
    void moveRight();
    void stopMoving();

    const float getX() const;
    const float getY() const;

private:
    float _dx, _dy;
    Direction _facing;

    bool _grounded;
};

#endif