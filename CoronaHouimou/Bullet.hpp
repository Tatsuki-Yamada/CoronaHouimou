#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include <cmath>
#include "Sprite.hpp"


class Bullet : public Sprite
{
private:
    Vector2 moveVec;
    float moveSpeed = 1;
    
public:
    int r;
    
    Bullet(Vector2 startPos, Vector2 targetPos, SDL_Renderer* targetRenderer) : Sprite(startPos.x, startPos.y, "PlayerBullet", targetRenderer)
    {
        SetReducRatio(0.1);
        
        double rad = atan2(targetPos.y - startPos.y, targetPos.x - startPos.x);
        moveVec.x = cos(rad) * moveSpeed * 10;          // あまりにも遅いと型の問題で速度が0になるため、10倍した値を基準にしている。
        moveVec.y = sin(rad) * moveSpeed * 10;
        
        r = GetReducSize().x / 2;
    }
    void Remake(Vector2 startPos, Vector2 targetPos);
    
    void Move();
};


#endif /* Bullet_hpp */
