#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Sprite.hpp"


class Button
{
private:
    Vector2 leftUp;
    Vector2 size;
    int r, g, b, a;
    bool isActive = true;
    
public:
    SDL_Renderer* renderer = nullptr;
    
    Button(Vector2 lu, Vector2 wh, int r, int g, int b, int a, SDL_Renderer* targetRenderer)
    {
        leftUp = lu;
        size = wh;
        renderer = targetRenderer;
    }
    
    bool CheckClick();
    void Redraw();
};

#endif /* Button_hpp */
