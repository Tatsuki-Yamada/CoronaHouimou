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
    Text* clickText;
    
    SDL_Renderer* renderer;
    
public:
    Title(SDL_Renderer* targetRenderer)
    {
        renderer = targetRenderer;

        titleText = new Text(170, 150, "コロナ包囲網", 50, targetRenderer, {255, 255, 255, 255});
        nameText = new Text(530, 450, "山田 竜暉", 20, targetRenderer, {255, 255, 255, 255});
        clickText = new Text(220, 300, "クリックで開始", 30, targetRenderer, {155, 155, 155, 255});
    }
    
    void Redraw();
};

#endif /* Title_hpp */
