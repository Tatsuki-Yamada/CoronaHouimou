#include "GameManager.hpp"


// ゲームに必要なオブジェクトを一通りまとめて生成する関数。
void GameManager::GameStart()
{
    player = new Player(0, 0, inGameRenderer);
    orange = new Enemy_Cupsule_Orange(5, 5, inGameRenderer);
    background = new Background(inGameRenderer);
    aim = new Aim(inGameRenderer);
}


// 各オブジェクトが毎フレーム行う処理をまとめた関数。
void GameManager::Update()
{
    // 照準をマウスカーソルに追従させる。
    aim->ChaseMouse();
    
    // 敵をプレイヤーに近づける。
    orange->MoveToPlayer(player->GetPos());
    
    // 敵がプレイヤーと当たったとき、敵をテレポートさせる。
    // TODO. 当たり判定のテスト用なので、いずれ弾と当たったときの処理に書き換える。
    if (orange->CheckHitBoxToCircle(player->r, player->GetCenterPos()))
        orange->Teleport(10, 10);
    
    /// キー入力の状態を見て、それに応じた処理を行う。
    /// 現時点で行っている処理->
    ///         プレイヤーの移動に応じた敵の移動
    ///         プレイヤーの移動に応じた背景の移動
    {
        if (KeyInput::Instance()->right)
        {
            orange->Right(-playerMoveSpeed);
            background->Right(-playerMoveSpeed);
        }
        if (KeyInput::Instance()->left)
        {
            orange->Left(-playerMoveSpeed);
            background->Left(-playerMoveSpeed);
        }
        if (KeyInput::Instance()->up)
        {
            orange->Up(-playerMoveSpeed);
            background->Up(-playerMoveSpeed);
        }
        if (KeyInput::Instance()->down)
        {
            orange->Down(-playerMoveSpeed);
            background->Down(-playerMoveSpeed);
        }
    }
}


// 描画をする関数。最後に描画したものほど前に来るため、描画順に注意。
// 存在しないものを描画しないようにnullチェックを行っているが、不要かもしれない。
void GameManager::Redraw()
{
    if (background != nullptr)
    {
        background->Redraw();
    }
    
    if (orange != nullptr)
    {
        orange->Redraw();
    }
    
    if (player != nullptr)
    {
        player->Redraw();
    }
    
    if (aim != nullptr)
    {
        aim->Redraw();
    }
}
