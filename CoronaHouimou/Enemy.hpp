#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"


class Enemy : public Sprite
{
private:
    float moveSpeed = 0.2;
    int hp;
    
public:
    Enemy(int x, int y, string type, SDL_Renderer* targetRenderer);
    void Init(int x, int y);
    void MoveTo(Vector2 targetPos);
    void TakeDamage(int d);
    bool CheckHitToCircle(int r, Vector2 CenterPos);
};


#endif /* Enemy_hpp */
