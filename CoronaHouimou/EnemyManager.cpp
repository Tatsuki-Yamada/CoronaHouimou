#include "EnemyManager.hpp"
#include "GameManager.hpp"


EnemyManager* EnemyManager::instance = nullptr;


// 敵を生成する関数。
void EnemyManager::SpawnEnemy()
{
    if (spawnCount < spawnLimit)
    {
        // 今フレームの時間を取得し、最後に敵を出したフレームからインターバル秒以上の間隔があれば敵を生成する。
        if (SDL_GetTicks() - lastSpawnTime > spawnInterval)
        {
            // 敵を沸かせる位置を8つからランダムに選択する。
            Vector2 inGamePos = GameManager::Instance()->inGamePos;
            int randIndex = rand() % 8;
            Vector2 spawnPos = spawnPoint[randIndex];
            spawnPos.x += -inGamePos.x + 320;
            spawnPos.y += -inGamePos.y + 240;
            
            // 配列内に無効状態の敵があればそれを使い回す。
            for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
            {
                if (!(*enemyItr)->isActive)
                {
                    (*enemyItr)->Init(spawnPos.x, spawnPos.y);
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


// 全EnemyのMoveTo()を呼び出す関数。
void EnemyManager::MoveEnemies(Vector2 playerPos)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->MoveTo(playerPos);
        
        ++enemyItr;
    }
}


// 全EnemyのRedraw()を呼び出す関数。
void EnemyManager::RedrawEnemies()
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        (*enemyItr)->Redraw();
        
        ++enemyItr;
    }
}


// 全EnemyのRight, Left, Up, Down()を呼び出す関数。
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


// 全EnemyにPlayerとの衝突判定をさせる関数。
void EnemyManager::CheckHitEnemiesToPlayer(Player* player)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        if ((*enemyItr)->CheckHitToCircle(player->r, player->GetPos()))
        {
            // 敵がプレイヤーと当たったときの処理。
            (*enemyItr)->isActive = false;
            GameManager::Instance()->playerHP--;
            GameManager::Instance()->enemyCount--;
            TextManager::Instance()->InfoUpdate();
        }
        
        ++enemyItr;
    }
}


// 全Enemyに全Bulletとの衝突判定をさせる関数。
void EnemyManager::CheckHitEnemiesToBullets(std::vector<Bullet*>* bullets)
{
    for (auto enemyItr = enemies.begin(); enemyItr != enemies.end();)
    {
        for (auto bulletItr = bullets->begin(); bulletItr != bullets->end();)
        {
            if ((*enemyItr)->CheckHitToCircle((*bulletItr)->r, (*bulletItr)->GetPos()))
            {
                // 敵が弾に当たったときの処理。
                (*enemyItr)->TakeDamage(GameManager::Instance()->playerAttackPower);
                (*bulletItr)->isActive = false;
                GameManager::Instance()->AddScore(100);
            }
            ++bulletItr;
        }
        
        ++enemyItr;
    }
}


// ウェーブが全滅したかチェックして返す関数。
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


// ウェーブを始めるときのリセットと難易度上昇を行う関数。
void EnemyManager::WaveStart()
{
    spawnCount = 0;
    spawnLimit += 2;
    spawnInterval -= 100;
    lastSpawnTime = SDL_GetTicks();
}


// リトライしたときに各変数をリセットする関数。
void EnemyManager::Reset()
{
    spawnInterval = 2000;
    spawnCount = 0;
    enemies = {};
}
