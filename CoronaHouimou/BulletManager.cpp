#include "BulletManager.hpp"


// 弾をプレイヤーから撃ち出す関数。
void BulletManager::CreateBullet(Vector2 startPos, Vector2 targetPos)
{
    // 今フレームの時間を取得し、最後に弾を撃ったフレームからインターバル秒以上の間隔があれば弾を撃つ。
    if (SDL_GetTicks() - lastShotTime > shotInterval)
    {
        cout << bullets.size() << endl;
        // 配列内に無効状態の弾があればそれを再度有効化して終わる。
        for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
        {
            if (!(*bulletItr)->isActive)
            {
                (*bulletItr)->Remake(startPos, targetPos);
                lastShotTime = SDL_GetTicks();
                return;
            }
            
            ++bulletItr;
        }
        bullets.push_back(new Bullet(startPos, targetPos, inGameRenderer));
        lastShotTime = SDL_GetTicks();
    }
}


void BulletManager::RedrawBullets()
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Redraw();
        
        ++bulletItr;
    }
}


void BulletManager::MoveBullets()
{
    for (auto bulletItr = bullets.begin(); bulletItr != bullets.end();)
    {
        (*bulletItr)->Move();
        
        ++bulletItr;
    }
}


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
