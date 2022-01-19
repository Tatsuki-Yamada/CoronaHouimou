#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "Text.hpp"


class Button : public Sprite
{
private:
    Text* text;
    
public:
    SDL_Renderer* renderer = nullptr;
    
    bool isActive = false;

    
    Button(Vector2 pos, const char* buttonType, const char* str, SDL_Renderer* targetRenderer) : Sprite(pos.x, pos.y, buttonType, targetRenderer)
    {
        renderer = targetRenderer;
        text = new Text(pos.x - w / 4, pos.y, str, 20, targetRenderer, {255, 255, 255, 255});
    }
    
    bool CheckClick();
    void Redraw();
};

#endif /* Button_hpp */
