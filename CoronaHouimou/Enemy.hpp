#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"

class Enemy : public Sprite
{
public:
    Enemy(int x, int y, string type, SDL_Renderer* targetRenderer) : Sprite(x, y, type, targetRenderer)
    {
        SetReducRatio(0.2);
    }
    
    void MoveToPlayer(Vector2 targetPos);
};


#endif /* Enemy_hpp */
