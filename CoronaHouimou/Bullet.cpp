#include "Bullet.hpp"
#include "GameManager.hpp"


//コンストラクタ。
Bullet::Bullet(Vector2 startPos, Vector2 targetPos, SDL_Renderer* targetRenderer) : Sprite(startPos.x, startPos.y, "PlayerBullet", targetRenderer)
{
    reducRatio = 0.1;
    r = GetReducSize().x / 2;

    Init(startPos, targetPos);
}


// 初期化処理をまとめた関数。
void Bullet::Init(Vector2 startPos, Vector2 targetPos)
{
    px = startPos.x;
    py = startPos.y;
    double rad = atan2(targetPos.y - startPos.y, targetPos.x - startPos.x);
    moveVec.x = cos(rad) * moveSpeed * 10;          // あまりにも遅いと型の問題で速度が0になるため、10倍した値を基準にしている。
    moveVec.y = sin(rad) * moveSpeed * 10;
    
    isActive = true;
}


// moveVec分移動する関数。
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
    else
    {
        px = 5000; py = 5000;
    }
}

