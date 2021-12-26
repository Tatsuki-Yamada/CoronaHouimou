#ifndef Background_hpp
#define Background_hpp

#include <stdio.h>
#include "Sprite.hpp"

class Background : public Sprite
{
public:
    Background(SDL_Renderer* targetRenderer) : Sprite(0, 0, "Background", targetRenderer)
    {
        ChangeReducRatio(2.0);
        SetPosToCenter();
    }
};

#endif /* Background_hpp */
