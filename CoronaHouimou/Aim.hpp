#ifndef Aim_hpp
#define Aim_hpp

#include <stdio.h>
#include "Sprite.hpp"


// Playerクラス
class Aim : public Sprite
{
public:
    Aim(SDL_Renderer* targetRenderer) : Sprite(0, 0, "Aim", targetRenderer)
    {
        SetReducRatio(0.2);
    }


};

#endif /* Aim_hpp */
