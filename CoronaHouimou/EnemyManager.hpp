#ifndef EnemyManager_hpp
#define EnemyManager_hpp

#include <vector>
#include "Enemy_Cupsule_Orange.hpp"
#include "Player.hpp"
#include "Bullet.hpp"


class EnemyManager
{
private:
    static EnemyManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    
    int lastSpawnTime = 0;          // 最後に敵が湧いた時間が入る変数。
    int spawnInterval = 2000;           // 敵が湧く間隔の変数。ミリ秒単位。
    int spawnCount = 0;         // このウェーブ中に何体の敵が湧いたかの変数。
    int basePos = 1000;         // 下のspawnPointを変更しやすくするためだけの変数。
    Vector2 spawnPoint[8] = {
        {-basePos, -basePos},
        {-0, -basePos},
        {basePos, -basePos},
        {-basePos, 0},
        {basePos, 0},
        {-basePos, basePos},
        {0, basePos},
        {basePos, basePos},
    };          // 敵が湧く座標の変数。
    
public:
    SDL_Renderer* inGameRenderer = nullptr;
    
    std::vector<Enemy_Cupsule_Orange*> enemies;         // 生成した敵を管理する変数。
    int spawnLimit = 10;            // 1ウェーブで計何体湧くかを示す変数。
    
    void MoveEnemies(Vector2 playerPos);
    void SpawnEnemy();
    void RedrawEnemies();
    void RightEnemies(int d, bool divR2);
    void LeftEnemies(int d, bool divR2);
    void UpEnemies(int d, bool divR2);
    void DownEnemies(int d, bool divR2);
    void CheckHitEnemiesToPlayer(Player* player);
    void CheckHitEnemiesToBullets(std::vector<Bullet*>* bullets);
    bool CheckWaveComplete();
    void WaveStart();
    void Reset();
    
    
    // Singleton化しているので、呼び出しのための中継を行う関数。
    static EnemyManager* Instance()
    {
        // インスタンスがまだ生成されていなければ、新しく生成して登録する。
        if (instance == NULL)
            instance = new EnemyManager();
        
        return instance;
    }
};

#endif /* EnemyManager_hpp */
