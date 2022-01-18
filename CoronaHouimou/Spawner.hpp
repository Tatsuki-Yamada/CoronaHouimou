#ifndef Spawner_hpp
#define Spawner_hpp

#include <stdio.h>
#include "Sprite.hpp"

class Spawner : public Sprite
{
public:
    Spawner(Vector2 pos, SDL_Renderer* targetRenderer) : Sprite(pos.x, pos.y, "Spawner", targetRenderer)
    {
        SetReducRatio(0.2);
    }
};

#endif /* Spawner_hpp */
