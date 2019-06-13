#include "game.hpp"
#include <iostream>
using namespace std;

int main(int argc, char ** argv)
{
    // Verbose mode for debug only

    if(argc > 1 and argv[1][1] == 'v')
    {
       Game::enableVerbose();
    }

    Game game;
    
    return 0;
}