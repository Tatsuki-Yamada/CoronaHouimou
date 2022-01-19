#include "Enemy.hpp"
#include "GameManager.hpp"


// コンストラクタ。
Enemy::Enemy(int x, int y, string type, SDL_Renderer* targetRenderer) : Sprite(x, y, type, targetRenderer)
{
    Init(x, y);
}


// 初期化処理をまとめた関数。
void Enemy::Init(int x, int y)
{
    px = x;
    py = y;
    hp = GameManager::Instance()->enemyDefaultHP;
    
    isActive = true;
}


// 引数の座標に向かって移動する関数。
void Enemy::MoveTo(Vector2 targetPos)
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
    

// ダメージを受ける処理をする関数。
void Enemy::TakeDamage(int d)
{
    hp -= d;
    
    if (hp <= 0)
    {
        GameManager::Instance()->enemyCount--;
        isActive = false;
    }
}


// 短形のオブジェクトから見て、円のオブジェクトが当たっているかの判定
bool Enemy::CheckHitToCircle(int r, Vector2 centerPos)
{
    Vector2 reducSize = GetReducSize();
    float rootedR = r / sqrt(2);
    
    Vector2 extendLeftUp = {int(px - reducSize.x / 2 - rootedR), int(py - reducSize.y / 2 - rootedR)};
    Vector2 extendRightDown = {int(px + reducSize.x / 2 + rootedR), int(py + reducSize.y / 2 + rootedR)};
    
    if (extendLeftUp.x <= centerPos.x && centerPos.x <= extendRightDown.x)
    {
        if (extendLeftUp.y <= centerPos.y && centerPos.y <= extendRightDown.y)
        {
            return true;
        }
    }
    
    return false;
}
