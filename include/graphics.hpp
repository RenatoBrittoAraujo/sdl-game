#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
public:
    Graphics();
    ~Graphics();
private:
    SDL_Window * _window;
    SDL_Renderer * _renderer;
};

#endif