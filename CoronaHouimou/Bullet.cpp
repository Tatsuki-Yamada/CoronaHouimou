#include "Bullet.hpp"
#include "GameManager.hpp"


void Bullet::Remake(Vector2 startPos, Vector2 targetPos)
{
    px = startPos.x;
    py = startPos.y;
    double rad = atan2(targetPos.y - startPos.y, targetPos.x - startPos.x);
    moveVec.x = cos(rad) * moveSpeed * 10;          // あまりにも遅いと型の問題で速度が0になるため、10倍した値を基準にしている。
    moveVec.y = sin(rad) * moveSpeed * 10;
    
    
    isActive = true;
}


void Bullet::Move()
{
    if (isActive)
    {
        Vector2 inGamePos = GameManager::Instance()->inGamePos;
        Vector2 halfWindow = {320, 240};            // 画面中央を起点としたいため、画面左上から中央までの距離を差し引きする用の変数。
        
        px += moveVec.x;
        py += moveVec.y;
        
        if (px + inGamePos.x - halfWindow.x <= -1000 || 1000 <= px + inGamePos.x - halfWindow.x)
        {
            isActive = false;
        }
        if (py + inGamePos.y - halfWindow.y <= -1000 || 1000 <= py + inGamePos.y - halfWindow.y)
        {
            isActive = false;
        }
        
    }
    
}

