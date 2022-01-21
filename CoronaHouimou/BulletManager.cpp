#include "BulletManager.hpp"


BulletManager* BulletManager::instance = nullptr;


// 弾をプレイヤーから撃ち出す関数。
void BulletManager::CreateBullet(Vector2 startPos, Vector2 targetPos)
{
    // 今フレームの時間を取得し、最後に弾を撃ったフレームからインターバル秒以上の間隔があれば弾を撃つ。
    if (SDL_GetTicks() - lastShotTime > shotInterval)
    {
        // 配列内に無効状態の弾があればそれを使い回す。
        for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
        {
            if (!(*bulletItr)->isActive)
            {
                (*bulletItr)->Init(startPos, targetPos);
                lastShotTime = SDL_GetTicks();
                return;
            }
            
            ++bulletItr;
        }
        bullets.push_back(new Bullet(startPos, targetPos, inGameRenderer));
        lastShotTime = SDL_GetTicks();
    }
}


// 全BulletのRedraw()を呼ぶ関数。
void BulletManager::RedrawBullets()
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Redraw();
        
        ++bulletItr;
    }
}


// 全BulletのMove()を呼ぶ関数。
void BulletManager::MoveBullets()
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Move();
        
        ++bulletItr;
    }
}


// 全BulletのRight, Left, Up, Down()を呼ぶ関数。
void BulletManager::RightBullets(int d, bool divR2)
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Right(d, divR2);
        
        ++bulletItr;
    }
}
void BulletManager::LeftBullets(int d, bool divR2)
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Left(d, divR2);
        
        ++bulletItr;
    }
}
void BulletManager::UpBullets(int d, bool divR2)
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Up(d, divR2);
        
        ++bulletItr;
    }
}
void BulletManager::DownBullets(int d, bool divR2)
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Down(d, divR2);
        
        ++bulletItr;
    }
}


// リトライしたときに各変数をリセットする関数。
void BulletManager::Reset()
{
    shotInterval = 500;
    bullets = {};
}
