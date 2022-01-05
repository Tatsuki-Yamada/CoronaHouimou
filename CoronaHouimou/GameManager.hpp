#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>

#include "Aim.hpp"
#include "Background.hpp"
#include "Enemy.hpp"
#include "Enemy_Cupsule_Orange.hpp"
#include "KeyManager.hpp"
#include "Player.hpp"
#include "Sprite.hpp"


class GameManager
{
public:
    SDL_Renderer* inGameRenderer = nullptr;
    
    Aim* aim = nullptr;
    Background* background = nullptr;
    Enemy* enemy = nullptr;
    Enemy_Cupsule_Orange* orange = nullptr;
    Player* player = nullptr;
    
    int playerMoveSpeed = 3;            // プレイヤーの移動速度。この数字に応じて背景や敵などのオブジェクトを移動させる。

    void GameStart();
    void Update();
    void Redraw();
};


#endif /* GameManager_hpp */
