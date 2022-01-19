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
    
    int lastSpawnTime = 0;
    int spawnInterval = 2000;
    int spawnCount = 0;
    int basePos = 1000;
    Vector2 spawnPoint[8] = {
        {-basePos, -basePos},
        {-0, -basePos},
        {basePos, -basePos},
        {-basePos, 0},
        {basePos, 0},
        {-basePos, basePos},
        {0, basePos},
        {basePos, basePos},
    };
    
public:
    SDL_Renderer* inGameRenderer = nullptr;
    
    std::vector<Enemy_Cupsule_Orange*> enemies;
    int spawnLimit = 10;

    
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
    void RedrawSpawners();
    void CreateSpawners();
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
