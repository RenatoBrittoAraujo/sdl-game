#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

struct SDL_Window;
struct SDL_Renderer;

#include <map>
#include <string>

class Graphics
{
public:
   
    Graphics();
    ~Graphics();

    SDL_Surface * loadImage(const std::string & path);

    void blitSurface(SDL_Texture * source, SDL_Rect * sourceRectagle, SDL_Rect * destinationRectangle);

    void flip();

    void clear();

    SDL_Renderer * getRenderer() const;

private:
  
    SDL_Window * _window;
    SDL_Renderer * _renderer;

    std::map<std::string, SDL_Surface *> _spriteSheets;

};

#endif