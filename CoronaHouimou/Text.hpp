#ifndef Text_hpp
#define Text_hpp

#include <stdio.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "iostream"


class Text
{
private:
    TTF_Font* font;
    SDL_Surface *surface;
    SDL_Texture *texture;
    const char* strings;
    int posX, posY;
    SDL_Color fontColor;
    
    SDL_Renderer* renderer;
    
public:
    Text(int x, int y, const char* str, int fontSize, SDL_Renderer* targetRenderer, SDL_Color color={0, 0, 0, 255})
    {
        posX = x;
        posY = y;
        strings = str;
        font = TTF_OpenFont("Fonts/komorebi-gothic.ttf", fontSize);
        fontColor = color;

        if (font == nullptr)
        {
            std::cout << "font error" << std::endl;
        }
        renderer = targetRenderer;
    }
    
    void Redraw();
};


#endif /* Text_hpp */
