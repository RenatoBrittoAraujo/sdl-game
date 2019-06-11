# Olá!
This is how I'm compiling for now, using c++17
```
g++ -std=c++17 -lSDL2main -lSDL2
```
If the file fails to compile like this in SDLtest.cpp there is probably something wrong with the lib

## Guide to running on linux

Install SDL2 with:
```
sudo apt-get install libsdl2-dev
```

Test if SDL2 is working by compiling the file SDLtest.cpp
```
g++ -std=c++17 SDLtest.cpp -lSDL2main -lSDL2
```

Install SDL2_Image with:
```
sudo apt-get install libsdl2-image-dev
```
