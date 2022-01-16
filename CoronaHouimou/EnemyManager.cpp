#include "EnemyManager.hpp"


EnemyManager* EnemyManager::instance = nullptr;


void EnemyManager::SpawnEnemy()
{
    // 今フレームの時間を取得し、最後に弾を撃ったフレームからインターバル秒以上の間隔があれば弾を撃つ。
    if (SDL_GetTicks() - lastSpawnTime > spawnInterval)
    {
        // 配列内に無効状態の弾があればそれを再度有効化して終わる。
        for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
        {
            if (!(*enemyItr)->isActive)
            {
                (*enemyItr)->Remake(5, 5);
                lastSpawnTime = SDL_GetTicks();
                return;
            }
            
            ++enemyItr;
        }
        enemies.push_back(new Enemy_Cupsule_Orange(0, 0, inGameRenderer));
        lastSpawnTime = SDL_GetTicks();
    }
}


void EnemyManager::MoveEnemies(Vector2 playerPos)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->MoveToPlayer(playerPos);
        
        ++enemyItr;
    }
}


void EnemyManager::RedrawEnemies()
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Redraw();
        
        ++enemyItr;
    }
}


void EnemyManager::RightEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Right(d, divR2);
        
        ++enemyItr;
    }
}


void EnemyManager::LeftEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Left(d, divR2);
        
        ++enemyItr;
    }
}


void EnemyManager::UpEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Up(d, divR2);
        
        ++enemyItr;
    }
}


void EnemyManager::DownEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Down(d, divR2);
        
        ++enemyItr;
    }
}


void EnemyManager::CheckHitEnemiesToPlayer(Player* player)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        // 敵がプレイヤーと当たったとき、敵をテレポートさせる。
        // TODO. 敵のテレポートを別の処理に置き換える。
        if ((*enemyItr)->CheckHitRectToCircle(player->r, player->GetPos()))
        {
            (*enemyItr)->Teleport(10, 10);
            player->TakeAttack();
        }
        
        ++enemyItr;
    }
}


void EnemyManager::CheckHitEnemiesToBullets(std::vector<Bullet*>* bullets)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        for (auto bulletItr = bullets->begin(); bulletItr != bullets->end();)
        {
            // 敵がプレイヤーと当たったとき、敵をテレポートさせる。
            // TODO. 敵のテレポートを別の処理に置き換える。
            if ((*enemyItr)->CheckHitRectToCircle((*bulletItr)->r, (*bulletItr)->GetPos()))
            {
                (*enemyItr)->isActive = false;
                (*bulletItr)->isActive = false;
            }
            ++bulletItr;
        }
        
        ++enemyItr;
    }
}
