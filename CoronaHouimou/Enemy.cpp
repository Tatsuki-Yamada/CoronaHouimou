#include "Enemy.hpp"


void Enemy::MoveToPlayer(Vector2 targetPos)
{
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
}
