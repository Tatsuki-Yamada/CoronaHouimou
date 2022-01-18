#include "GameManager.hpp"


GameManager* GameManager::instance = nullptr;


// ゲームに必要なオブジェクトを一通りまとめて生成する関数。
void GameManager::GameStart()
{
    player = new Player(0, 0, inGameRenderer);
    background = new Background(inGameRenderer);
    aim = new Aim(inGameRenderer);
    attackUpButton = new Button({320, 100}, "Button_Rect_Red", "攻撃力上昇", inGameRenderer);
    moveUpButton = new Button({178, 380}, "Button_Rect_Green", "移動速度上昇", inGameRenderer);
    shotSpeedUpButton = new Button({462, 380}, "Button_Rect_Blue", "連射速度上昇", inGameRenderer);

}


// 各オブジェクトが毎フレーム行う処理をまとめた関数。
void GameManager::Update()
{
    //cout << inGamePos.x << ", " << inGamePos.y << endl;           // inGamePosを確認したいときにコメント解除する。

    
    // 照準をマウスカーソルに追従させる。
    aim->ChaseMouse();
        
    // 敵が全滅していなければ
    if (isAttacking)
    {
        // 敵をスポーンさせる
        EnemyManager::Instance()->SpawnEnemy();

        // 敵をプレイヤーに近づけさせる。
        EnemyManager::Instance()->MoveEnemies(player->GetPos());

        // 敵の当たり判定を判定させる。
        EnemyManager::Instance()->CheckHitEnemiesToPlayer(player);
        EnemyManager::Instance()->CheckHitEnemiesToBullets(&(BulletManager::Instance()->bullets));
        
        // 敵を全滅させたときの処理をする。
        if (EnemyManager::Instance()->CheckWaveComplete())
        {
            attackUpButton->isActive = true;
            moveUpButton->isActive = true;
            shotSpeedUpButton->isActive = true;
            isAttacking = false;
        }
        
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
        }
    }
    else
    {
        if (KeyManager::Instance()->leftClick)
        {
            if (attackUpButton->CheckClick())
            {
                playerAttackPower += 1;
                
                WaveStart();
            }
            else if(moveUpButton->CheckClick())
            {
                playerMoveSpeed += 1;
                WaveStart();
            }
            else if (shotSpeedUpButton->CheckClick())
            {
                BulletManager::Instance()->shotInterval -= 50;
                WaveStart();
            }
        }
    }
}


// 描画をする関数。最後に描画したものほど前に来るため、描画順に注意。
void GameManager::Redraw()
{
    background->Redraw();
    EnemyManager::Instance()->RedrawSpawners();
    player->Redraw();

    
    if (isAttacking)
    {
        EnemyManager::Instance()->RedrawEnemies();
        BulletManager::Instance()->RedrawBullets();
    }
    else
    {
        attackUpButton->Redraw();
        moveUpButton->Redraw();
        shotSpeedUpButton->Redraw();
    }
    
    aim->Redraw();
    
    TextManager::Instance()->Redraw();

}


void GameManager::AddScore(int s)
{
    score += s;
}


void GameManager::WaveStart()
{
    EnemyManager::Instance()->WaveStart();
    enemyDefaultHP++;
    
    isAttacking = true;
}
