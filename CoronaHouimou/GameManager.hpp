#ifndef GameManager_hpp
#define GameManager_hpp

#include "Aim.hpp"
#include "Background.hpp"
#include "BulletManager.hpp"
#include "Button.hpp"
#include "Enemy_Cupsule_Orange.hpp"
#include "EnemyManager.hpp"
#include "KeyManager.hpp"
#include "Player.hpp"
#include "TextManager.hpp"


class GameManager
{
private:
    static GameManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    bool isAttacking = true;            // ウェーブ中かを示す変数、

public:
    SDL_Renderer* inGameRenderer = nullptr;
    
    Aim* aim = nullptr;         // 照準オブジェクト。
    Background* background = nullptr;           // 背景オブジェクト。
    Player* player = nullptr;           // プレイヤーオブジェクト。
    Button* attackUpButton = nullptr;           // 攻撃力上昇ボタン。
    Button* moveUpButton = nullptr;         // 移動速度上昇ボタン。
    Button* shotSpeedUpButton = nullptr;            // 連射速度上昇ボタン。
    int playerMoveSpeed = 3;            // プレイヤーの移動速度。この数字に応じて背景や敵などのオブジェクトを移動させる。
    int playerAttackPower = 10;          // プレイヤーの攻撃力。
    int playerHP = 5;           // プレイヤーのHP。
    int enemyDefaultHP = 10;         // 敵のこのWaveでの最大HP
    int enemyCount = 10;            // 現在の敵の数を示す変数。
    Vector2 inGamePos = {0, 0};         // プレイヤーのゲーム内座標。
    int moveLimit = 700;           // プレイヤーのゲーム内座標の移動限界値。この数値の正方形フィールドから出られない。
    int score = 0;          // 獲得したスコア。

    void Init();
    void Update();
    void Redraw();
    void AddScore(int s);
    void WaveStart();
    void Reset();
    
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
