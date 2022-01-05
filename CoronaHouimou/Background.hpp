#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include "Sprite.hpp"

class Background : public Sprite
{
public:
    Background(SDL_Renderer* targetRenderer) : Sprite(0, 0, "Background", targetRenderer)
    {
        SetReducRatio(2.0);
        SetPosToCenter();
    }
    
    void Redraw();
};

#endif /* Background_hpp */
