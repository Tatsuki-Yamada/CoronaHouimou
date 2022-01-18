#ifndef BulletManager_hpp
#define BulletManager_hpp

#include <stdio.h>
#include <vector>
#include "Bullet.hpp"
#include "GameManager.hpp"


/// <summary>
/// キー入力状態をそれぞれのフラグで管理しているクラス。
/// Singleton化しているため、必ずInstance()関数を呼び出した上で使用する。
/// 使用例；BulletManager::Instance()->RedrawBullets();
/// </summary>
class BulletManager
{
private:
    static BulletManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    
    int lastShotTime = 0;         // 連射のインターバルのため、最後に弾を撃った時間を保存する変数。
    
public:
    SDL_Renderer* inGameRenderer = nullptr;
    
    std::vector<Bullet*> bullets;
    int shotInterval = 500;           // 連射のインターバルを設定する変数。ミリ秒単位。

    
    void CreateBullet(Vector2 startPos, Vector2 targetPos);
    void RedrawBullets();
    void MoveBullets();
    void RightBullets(int v, bool divR2 = false);
    void LeftBullets(int v, bool divR2 = false);
    void UpBullets(int v, bool divR2 = false);
    void DownBullets(int v, bool divR2 = false);
    
    // Singleton化しているので、呼び出しのための中継を行う関数。
    static BulletManager* Instance()
    {
        // インスタンスがまだ生成されていなければ、新しく生成して登録する。
        if (instance == NULL)
            instance = new BulletManager();
        
        return instance;
    }
};

#endif /* BulletManager_hpp */
