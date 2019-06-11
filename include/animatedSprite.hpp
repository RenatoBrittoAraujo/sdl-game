#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include "sprite.hpp"
#include "globals.hpp"
#include <map>
#include <string>
#include <vector>


class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite();
    AnimatedSprite(Graphics & graphics, const std::string & path, int sourceX, int sourceY,
                   int width, int height, float posX, float posY, float timeToUpdate);
    void playAnimation(std::string, bool once = false);
    void update(int elapsedTime);
    void draw(Graphics & graphics, int x, int y);
    virtual void setupAnimation();

protected:
    double _timeToUpdate;
    bool _currentAnimationOnce;
    std::string _currentAnimation;

    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

    void resetAnimations();

    void stopAnimation();

    void setVisible(bool visible);

    virtual void animationOnce(std::string currentAnimation);    

private:
    std::map< std::string, std::vector<SDL_Rect>  > _animations;
    std::map< std::string, Vector2 > _offsets;
    int _frameIndex;
    double _timeElapsed;
    bool _visible;
};

#endif