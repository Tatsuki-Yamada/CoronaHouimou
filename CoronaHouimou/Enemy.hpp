#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"

class Enemy : public Sprite
{
private:
    float moveSpeed = 0.2;
    int hp = 2;
    
public:
    Enemy(int x, int y, string type, SDL_Renderer* targetRenderer);
    
    void MoveToPlayer(Vector2 targetPos);
    
    void Remake(int x, int y);
    void TakeDamage(int d);
};


#endif /* Enemy_hpp */
