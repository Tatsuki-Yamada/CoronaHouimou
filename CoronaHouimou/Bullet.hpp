#ifndef Bullet_hpp
#define Bullet_hpp

#include <cmath>
#include "Sprite.hpp"


class Bullet : public Sprite
{
private:
    Vector2 moveVec;
    float moveSpeed = 1;
    
public:
    int r;
    
    Bullet(Vector2 startPos, Vector2 targetPos, SDL_Renderer* targetRenderer);
    void Init(Vector2 startPos, Vector2 targetPos);
    void Move();
};


#endif /* Bullet_hpp */
