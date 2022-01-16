#include "Enemy.hpp"


void Enemy::MoveToPlayer(Vector2 targetPos)
{
    if (isActive)
    {
        /*
        if (px > targetPos.x)
        {
            px -= 1;
        }
        else if (px < targetPos.x)
        {
            px += 1;
        }
        
        if (py > targetPos.y)
        {
            py -= 1;
        }
        else if (py < targetPos.y)
        {
            py += 1;
        }
         */
         //TODO. 敵の移動厳密化の製作中
        
        double rad = atan2(targetPos.y - py, targetPos.x - px);
        px += cos(rad) * moveSpeed * 10;          // あまりにも遅いと型の問題で速度が0になるため、10倍した値を基準にしている。
        py += sin(rad) * moveSpeed * 10;
    }
    else
    {
        px = -5000; py = -5000;
    }
}
    


void Enemy::Remake(int x, int y)
{
    px = x;
    py = y;
    
    isActive = true;
}
