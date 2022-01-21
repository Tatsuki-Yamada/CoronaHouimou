#include "GameManager.hpp"
#include <string>


GameManager* GameManager::instance = nullptr;


// ゲームに必要なオブジェクトを一通りまとめて生成する関数。
void GameManager::Init()
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
    // 照準をマウスカーソルに追従させる。
    aim->ChaseMouse();
        
    // 戦闘中
    if (isAttacking)
    {
        // 敵をスポーンさせる
        EnemyManager::Instance()->SpawnEnemy();

        // 敵をプレイヤーに近づけさせる。
        EnemyManager::Instance()->MoveEnemies(player->GetPos());

        // 敵の衝突判定をさせる。
        EnemyManager::Instance()->CheckHitEnemiesToPlayer(player);
        EnemyManager::Instance()->CheckHitEnemiesToBullets(&(BulletManager::Instance()->bullets));
        
        // 敵を全滅させたときの処理をする。
        if (EnemyManager::Instance()->CheckWaveComplete())
        {
            attackUpButton->isActive = true;
            moveUpButton->isActive = true;
            
            if (BulletManager::Instance()->shotInterval >= 51)
            {
                shotSpeedUpButton->isActive = true;
            }
            isAttacking = false;
        }
        
        // 弾を移動させる。
        BulletManager::Instance()->MoveBullets();
        
        /// キー入力の状態を見て、それに応じた処理を行う。
        /// 現時点で行っている処理->
        ///     斜め移動を検知する。
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
        
        // スペースキーで弾の発射
        if (KeyManager::Instance()->space)
        {
            BulletManager::Instance()->CreateBullet(player->GetPos(), aim->GetPos());
        }
    }
    // 変異の選択中
    else
    {
        if (KeyManager::Instance()->leftClick)
        {
            if (attackUpButton->CheckClick())
            {
                playerAttackPower *= 1.3;
                
                WaveStart();
            }
            else if(moveUpButton->CheckClick())
            {
                playerMoveSpeed += 1;
                WaveStart();
            }
            else if (shotSpeedUpButton->CheckClick())
            {
                BulletManager::Instance()->shotInterval /= 1.3;
                WaveStart();
            }
        }
    }
}


// 描画をする関数。最後に描画したものほど前に来るため、描画順に注意。
void GameManager::Redraw()
{
    background->Redraw();
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


// スコアを加算する関数。
void GameManager::AddScore(int s)
{
    score += s * playerAttackPower;
    TextManager::Instance()->InfoUpdate();
}


// ウェーブを始めるときのリセットと難易度上昇を行う関数。
void GameManager::WaveStart()
{
    EnemyManager::Instance()->WaveStart();
    enemyDefaultHP *= 1.5;
    enemyCount = EnemyManager::Instance()->spawnLimit;
    TextManager::Instance()->InfoUpdate();
    
    isAttacking = true;
}


// リトライしたときに各変数をリセットする関数。
void GameManager::Reset()
{
    playerMoveSpeed = 3;
    playerAttackPower = 10;
    playerHP = 5;
    enemyDefaultHP = 10;
    enemyCount = 10;
    inGamePos = {0, 0};
    score = 0;
    background->Teleport(320, 240);
}
