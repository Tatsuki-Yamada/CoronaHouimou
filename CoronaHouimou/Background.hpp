#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include "Sprite.hpp"

class Background : public Sprite
{
public:
    Background(SDL_Renderer* targetRenderer) : Sprite(320, 240, "Background", targetRenderer)
    {
        SetReducRatio(2.5);
        SetPosToCenter();
    }
    
    void Redraw();
};

#endif /* Background_hpp */
