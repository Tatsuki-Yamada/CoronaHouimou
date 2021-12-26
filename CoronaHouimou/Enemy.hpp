#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"

class Enemy : public Sprite
{
public:
    Enemy(int x, int y, string type, SDL_Renderer* targetRenderer) : Sprite(x, y, type, targetRenderer)
    {
        ChangeReducRatio(0.2);
    }
    
    void MoveToPlayer();
};


#endif /* Enemy_hpp */
