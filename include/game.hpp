#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "level.hpp"

class Graphics;

class Game
{
public:
    Game();
    ~Game();

    static void enableVerbose();

private:
    void gameLoop();
    void draw(Graphics & graphics);
    void update(float time);

    Player _player;
    Level _level;

    bool _gameRunning = true;
};

#endif