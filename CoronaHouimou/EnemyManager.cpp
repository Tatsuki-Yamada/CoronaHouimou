#include "EnemyManager.hpp"
#include "GameManager.hpp"



EnemyManager* EnemyManager::instance = nullptr;


void EnemyManager::SpawnEnemy()
{
    if (spawnCount < spawnLimit)
    {
        // 今フレームの時間を取得し、最後に敵を出したフレームからインターバル秒以上の間隔があれば敵を生成する。
        if (SDL_GetTicks() - lastSpawnTime > spawnInterval)
        {
            Vector2 inGamePos = GameManager::Instance()->inGamePos;
            int randIndex = rand() % 8;
            Vector2 spawnPos = spawnPoint[randIndex];
            spawnPos.x += -inGamePos.x + 320;
            spawnPos.y += -inGamePos.y + 240;
            
            // 配列内に無効状態の敵があればそれを再度有効化して終わる。
            for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
            {
                if (!(*enemyItr)->isActive)
                {
                    (*enemyItr)->Remake(spawnPos.x, spawnPos.y);
                    lastSpawnTime = SDL_GetTicks();
                    spawnCount++;

                    return;
                }
                
                ++enemyItr;
            }
            enemies.push_back(new Enemy_Cupsule_Orange(spawnPos.x, spawnPos.y, inGameRenderer));
            lastSpawnTime = SDL_GetTicks();
            
            spawnCount++;
        }
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
    
    /*
    for (Spawner* s : spawners)
    {
        s->Right(d, divR2);
    }
     */
}


void EnemyManager::LeftEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Left(d, divR2);
        
        ++enemyItr;
    }
    
    /*
    for (Spawner* s : spawners)
    {
        s->Left(d, divR2);
    }
     */
}


void EnemyManager::UpEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Up(d, divR2);
        
        ++enemyItr;
    }
    
    /*
    for (Spawner* s : spawners)
    {
        s->Up(d, divR2);
    }
     */
}


void EnemyManager::DownEnemies(int d, bool divR2)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Down(d, divR2);
        
        ++enemyItr;
    }
    
    /*
    for (Spawner* s : spawners)
    {
        s->Down(d, divR2);
    }
     */
}


void EnemyManager::CheckHitEnemiesToPlayer(Player* player)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        // 敵がプレイヤーと当たったとき、敵をテレポートさせる。
        // TODO. 敵のテレポートを別の処理に置き換える。
        if ((*enemyItr)->CheckHitRectToCircle(player->r, player->GetPos()))
        {
            (*enemyItr)->isActive = false;
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
            if ((*enemyItr)->CheckHitRectToCircle((*bulletItr)->r, (*bulletItr)->GetPos()))
            {
                (*enemyItr)->TakeDamage(GameManager::Instance()->playerAttackPower);
                (*bulletItr)->isActive = false;
                GameManager::Instance()->AddScore(100);
            }
            ++bulletItr;
        }
        
        ++enemyItr;
    }
}


bool EnemyManager::CheckWaveComplete()
{
    if (spawnCount >= spawnLimit)
    {
        for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
        {
            // まだ動いている敵がいるならfalseを返す
            if ((*enemyItr)->isActive)
            {
                return false;
            }
            
            ++enemyItr;
        }
        
        return true;
    }
    
    return false;
}



void EnemyManager::WaveStart()
{
    spawnCount = 0;
    spawnLimit += 2;
    spawnInterval -= 100;
    lastSpawnTime = SDL_GetTicks();
}


void EnemyManager::RedrawSpawners()
{
    /*
    for (Spawner* s : spawners)
    {
        (s)->Redraw();
    }
     */
}


void EnemyManager::CreateSpawners()
{
    /*
    for (int i = 0; i < 8; i++)
    {
        Spawner* s = new Spawner(Vector2{spawnPoint[i].x + 320, spawnPoint[i].y + 240}, inGameRenderer);
        spawners[i] = s;
    }
     */
}


void EnemyManager::Reset()
{
    spawnInterval = 2000;
    spawnCount = 0;
    enemies = {};
}
