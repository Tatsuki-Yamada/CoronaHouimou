#include "Enemy.hpp"
#include "GameManager.hpp"


Enemy::Enemy(int x, int y, string type, SDL_Renderer* targetRenderer) : Sprite(x, y, type, targetRenderer)
{
    SetReducRatio(0.2);
    hp = GameManager::Instance()->enemyDefaultHP;
}


void Enemy::MoveToPlayer(Vector2 targetPos)
{
    if (isActive)
    {
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
    hp = GameManager::Instance()->enemyDefaultHP;
    
    isActive = true;
}


void Enemy::TakeDamage(int d)
{
    hp -= d;
    
    if (hp <= 0)
        isActive = false;
}
