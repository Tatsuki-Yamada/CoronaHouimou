#ifndef Title_hpp
#define Title_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"



class Title
{
private:
    Text* titleText;
    Text* nameText;
    
    SDL_Renderer* renderer;
    
public:
    Title(SDL_Renderer* targetRenderer)
    {
        renderer = targetRenderer;

        titleText = new Text(200, 200, "コロナ包囲網", 40, targetRenderer, {255, 255, 255, 255});
        nameText = new Text(300, 350, "山田 竜暉", 30, targetRenderer, {255, 255, 255, 255});
    }
    
    void Redraw();
};

#endif /* Title_hpp */
