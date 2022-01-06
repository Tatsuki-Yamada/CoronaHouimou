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
    if (orange->CheckHitRectToCircle(player->r, player->GetPos()))
        orange->Teleport(10, 10);
    
    BulletManager::Instance()->MoveBullets();
    
    /// キー入力の状態を見て、それに応じた処理を行う。
    /// 現時点で行っている処理->
    ///         プレイヤーの移動に応じた敵の移動
    ///         プレイヤーの移動に応じた背景の移動
    ///         プレイヤーの移動に応じた弾の移動
    {
        // プレイヤーが斜め移動をするとき、移動量にルート2を割るフラグを渡す。
        bool divR2 = false;
        if ((KeyManager::Instance()->right || KeyManager::Instance()->left) && (KeyManager::Instance()->up || KeyManager::Instance()->down))
            divR2 = true;
        
        
        if (KeyManager::Instance()->right)
        {
            orange->Left(playerMoveSpeed, divR2);
            background->Left(playerMoveSpeed, divR2);
            BulletManager::Instance()->LeftBullets(playerMoveSpeed, divR2);
        }
        if (KeyManager::Instance()->left)
        {
            orange->Right(playerMoveSpeed, divR2);
            background->Right(playerMoveSpeed, divR2);
            BulletManager::Instance()->RightBullets(playerMoveSpeed, divR2);
        }
        if (KeyManager::Instance()->up)
        {
            orange->Down(playerMoveSpeed, divR2);
            background->Down(playerMoveSpeed, divR2);
            BulletManager::Instance()->DownBullets(playerMoveSpeed, divR2);
        }
        if (KeyManager::Instance()->down)
        {
            orange->Up(playerMoveSpeed, divR2);
            background->Up(playerMoveSpeed, divR2);
            BulletManager::Instance()->UpBullets(playerMoveSpeed, divR2);
        }
        if (KeyManager::Instance()->leftClick || KeyManager::Instance()->space)
        {
            BulletManager::Instance()->CreateBullet(player->GetPos(), aim->GetPos());
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
    
    BulletManager::Instance()->RedrawBullets();
}
