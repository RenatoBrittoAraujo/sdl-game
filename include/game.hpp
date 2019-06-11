#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"

class Graphics;

class Game
{
public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw(Graphics & graphics);
    void update(float time);

    Player _player;
};

#endif