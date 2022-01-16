#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"

class Enemy : public Sprite
{
private:
    float moveSpeed = 0.2;
    
public:
    Enemy(int x, int y, string type, SDL_Renderer* targetRenderer) : Sprite(x, y, type, targetRenderer)
    {
        SetReducRatio(0.2);
    }
    
    void MoveToPlayer(Vector2 targetPos);
    
    void Remake(int x, int y);
};


#endif /* Enemy_hpp */
