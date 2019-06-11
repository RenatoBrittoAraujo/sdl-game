#ifndef GAME_HPP
#define GAME_HPP

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
};

#endif