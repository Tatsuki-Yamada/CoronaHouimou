#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>

#include "Aim.hpp"
#include "Background.hpp"
#include "BulletManager.hpp"
#include "Button.hpp"
#include "Enemy.hpp"
#include "Enemy_Cupsule_Orange.hpp"
#include "EnemyManager.hpp"
#include "KeyManager.hpp"
#include "Player.hpp"
#include "Sprite.hpp"
#include "TextManager.hpp"




class GameManager
{
private:
    static GameManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    bool isAttacking = true;

public:
    SDL_Renderer* inGameRenderer = nullptr;
    
    Aim* aim = nullptr;
    Background* background = nullptr;
    Enemy* enemy = nullptr;
    Enemy_Cupsule_Orange* orange = nullptr;
    Player* player = nullptr;
    Button* attackUpButton = nullptr;
    Button* moveUpButton = nullptr;
    Button* shotSpeedUpButton = nullptr;

    
    
    int playerMoveSpeed = 3;            // プレイヤーの移動速度。この数字に応じて背景や敵などのオブジェクトを移動させる。
    int playerAttackPower = 1;          // プレイヤーの攻撃力。
    int enemyDefaultHP = 1;         // 敵のこのWaveでの最大HP
    Vector2 inGamePos = {0, 0};         // プレイヤーのゲーム内座標。
    int moveLimit = 700;           // プレイヤーのゲーム内座標の移動限界値。この数値の正方形フィールドから出られない。
    int score = 0;          // 獲得したスコア。

    void GameStart();
    void Update();
    void Redraw();
    void AddScore(int s);
    void WaveStart();
    
    
    // Singleton化しているので、呼び出しのための中継を行う関数。
    static GameManager* Instance()
    {
        // インスタンスがまだ生成されていなければ、新しく生成して登録する。
        if (instance == NULL)
            instance = new GameManager();
        
        return instance;
    }
};


#endif /* GameManager_hpp */
