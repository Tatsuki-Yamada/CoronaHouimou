#include "GameManager.hpp"


GameManager* GameManager::instance = nullptr;


// ゲームに必要なオブジェクトを一通りまとめて生成する関数。
void GameManager::GameStart()
{
    player = new Player(0, 0, inGameRenderer);
    background = new Background(inGameRenderer);
    aim = new Aim(inGameRenderer);
    testButton = new Button({50, 50}, {200, 200}, 200, 200, 200, 255, inGameRenderer);
}


// 各オブジェクトが毎フレーム行う処理をまとめた関数。
void GameManager::Update()
{
    //cout << inGamePos.x << ", " << inGamePos.y << endl;           // inGamePosを確認したいときにコメント解除する。

    
    // 照準をマウスカーソルに追従させる。
    aim->ChaseMouse();
    
    // 敵をスポーンさせる
    EnemyManager::Instance()->SpawnEnemy();

    // 敵をプレイヤーに近づけさせる。
    EnemyManager::Instance()->MoveEnemies(player->GetPos());

    // 敵の当たり判定を判定させる。
    EnemyManager::Instance()->CheckHitEnemiesToPlayer(player);
    EnemyManager::Instance()->CheckHitEnemiesToBullets(&(BulletManager::Instance()->bullets));
    
    // 弾を移動させる。
    BulletManager::Instance()->MoveBullets();
    
    /// キー入力の状態を見て、それに応じた処理を行う。
    /// 現時点で行っている処理->
    ///         現時点でのゲーム内座標を一時保存する。
    ///         ゲーム内座標を移動させる。
    ///         if (ゲーム内座標が制限を超えたら)
    ///             元の座標に戻す。
    ///         else
    ///             プレイヤーの移動に応じた敵の移動
    ///             プレイヤーの移動に応じた背景の移動
    ///             プレイヤーの移動に応じた弾の移動
    {
        // プレイヤーが斜め移動をするとき、移動量にルート2を割るフラグを渡す。
        bool divR2 = false;
        if ((KeyManager::Instance()->right || KeyManager::Instance()->left) && (KeyManager::Instance()->up || KeyManager::Instance()->down))
            divR2 = true;
        
        // 右移動
        if (KeyManager::Instance()->right)
        {
            Vector2 prevInGamePos = inGamePos;
            inGamePos.x += divR2 ? playerMoveSpeed * sqrt(2) : playerMoveSpeed;
            
            if (inGamePos.x > moveLimit)
            {
                inGamePos = prevInGamePos;
            }
            else
            {
                EnemyManager::Instance()->LeftEnemies(playerMoveSpeed, divR2);
                background->Left(playerMoveSpeed, divR2);
                BulletManager::Instance()->LeftBullets(playerMoveSpeed, divR2);
            }
        }
        // 左移動
        if (KeyManager::Instance()->left)
        {
            Vector2 prevInGamePos = inGamePos;
            inGamePos.x -= divR2 ? playerMoveSpeed * sqrt(2) : playerMoveSpeed;

            if (inGamePos.x < -moveLimit)
            {
                inGamePos = prevInGamePos;
            }
            else
            {
                EnemyManager::Instance()->RightEnemies(playerMoveSpeed, divR2);
                background->Right(playerMoveSpeed, divR2);
                BulletManager::Instance()->RightBullets(playerMoveSpeed, divR2);
            }
        }
        // 上移動
        if (KeyManager::Instance()->up)
        {
            Vector2 prevInGamePos = inGamePos;
            inGamePos.y -= divR2 ? playerMoveSpeed * sqrt(2) : playerMoveSpeed;

            if (inGamePos.y < -moveLimit)
            {
                inGamePos = prevInGamePos;
            }
            else
            {
                EnemyManager::Instance()->DownEnemies(playerMoveSpeed, divR2);
                background->Down(playerMoveSpeed, divR2);
                BulletManager::Instance()->DownBullets(playerMoveSpeed, divR2);
            }
        }
        // 下移動
        if (KeyManager::Instance()->down)
        {
            Vector2 prevInGamePos = inGamePos;
            inGamePos.y += divR2 ? playerMoveSpeed * sqrt(2) : playerMoveSpeed;

            if (inGamePos.y > moveLimit)
            {
                inGamePos = prevInGamePos;
            }
            else
            {
                EnemyManager::Instance()->UpEnemies(playerMoveSpeed, divR2);
                background->Up(playerMoveSpeed, divR2);
                BulletManager::Instance()->UpBullets(playerMoveSpeed, divR2);
            }
        }
        if (KeyManager::Instance()->leftClick || KeyManager::Instance()->space)
        {
            BulletManager::Instance()->CreateBullet(player->GetPos(), aim->GetPos());
            testButton->CheckClick();
        }
    }
}


// 描画をする関数。最後に描画したものほど前に来るため、描画順に注意。
void GameManager::Redraw()
{
    background->Redraw();
    player->Redraw();
    EnemyManager::Instance()->RedrawEnemies();
    BulletManager::Instance()->RedrawBullets();
    aim->Redraw();
    
    testButton->Redraw();

}
