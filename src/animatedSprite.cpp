#include "animatedSprite.hpp"
#include "sprite.hpp"
#include "graphics.hpp"
#include <string>
#include <vector>

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & path, int sourceX, int sourceY, 
                                int width, int height, float posX, float posY, float timeToUpdate) :
                                Sprite(graphics, path, sourceX, sourceY, width, height, posX, posY),
                                _frameIndex(0),
                                _timeToUpdate(timeToUpdate),
                                _visible(true),
                                _currentAnimationOnce(false),
                                _currentAnimation("")
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
    std::vector<SDL_Rect> rectangles;
    for(int i = 0; i < frames; i++)
    {
        SDL_Rect newRect = { (i + x) * width, y, width, height };
        rectangles.push_back(newRect);
    }
    this->_animations.insert({ name, rectangles });
    this->_offsets.insert({ name , offset });
}

void AnimatedSprite::resetAnimations()
{
    this->_animations.clear();
    this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
    if(!_animations.count(animation))
    {
        throw "Failed at fiding animation type | Class: AnimatedSprite";
    }
    this->_currentAnimationOnce = once;
    if(this->_currentAnimation != animation)
    {
        this->_currentAnimation = animation;
        this->_currentAnimation = animation;
        this->_frameIndex = 0;
    }
}

void AnimatedSprite::setVisible(bool visible)
{
    this->_visible = visible;
}

void AnimatedSprite::stopAnimation()
{
    this->_frameIndex = 0;
}

void AnimatedSprite::update(int elapsedTime)
{
    Sprite::update();
    this->_timeElapsed += elapsedTime;
    if(this->_timeElapsed > this->_timeToUpdate)
    {
        this->_timeElapsed -= this->_timeToUpdate;
        if(_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
        {
            this->_frameIndex++;
        }
        else
        {
            if(_currentAnimationOnce)
            {
                this->setVisible(false);
            }
            this->_frameIndex = 0;
        }   
    }
}

void AnimatedSprite::draw(Graphics & graphics, int x, int y)
{
    if(this->_visible)
    {
        SDL_Rect destination;
        destination.x = x + this->_offsets[this->_currentAnimation].x;
        destination.y = y + this->_offsets[this->_currentAnimation].y;
        destination.w = this->_sourceRect.w * globals::SPRITE_SCALE;
        destination.h = this->_sourceRect.h * globals::SPRITE_SCALE;
        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
        graphics.blitSurface(this->_spriteSheet, & sourceRect, & destination);
    }
}

void AnimatedSprite::animationDone(std::string currentAnimation)
{

}