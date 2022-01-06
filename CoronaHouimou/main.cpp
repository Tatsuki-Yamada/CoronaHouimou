#include <iostream>
#include <SDL2/SDL.h>

#include "GameManager.hpp"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL;

KeyManager* KeyManager::instance = nullptr;         // Singletonを使うとき、初期化が必要らしい。できれば他の場所に移したい。
BulletManager* BulletManager::instance = nullptr;


// SDL周りの初期化をまとめて行う関数。
bool Init()
{
    // 初期化に失敗したらfalseを返す。
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << "SDL_Init failed.";
        return false;
    }

    window = SDL_CreateWindow("コロナ包囲網",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    mainRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(mainRenderer, 200, 200, 200, 255);
        
    return true;
}


// メイン関数
int main(int argc, const char * argv[])
{
    // SDLの初期化を行う。初期化に失敗したとき、プログラムを終了させる。
    if (!Init())
        return -1;

    // ゲームマネージャーを生成する。
    GameManager* gameManager = new GameManager();
    gameManager->inGameRenderer = mainRenderer;
    gameManager->GameStart();
    
    // 弾のマネージャーにレンダラーを設定する。
    BulletManager::Instance()->inGameRenderer = mainRenderer;
    
    // フレームレートを調整する為の変数を生成する。
    int prevFrameEndTime = 0, nowFrameStartTime;

    // メインループで使う変数を生成する。
    SDL_Event e;
    bool quit = false;
    
    // メインループを行う。
    while (!quit)
    {
        // フレームレート固定のため、今フレームの処理が始まった時間を取得する。
        nowFrameStartTime = SDL_GetTicks();
        
        // 前フレームと今フレームの時間を見て、差が16ミリ秒以内の場合は16ミリ秒の差が出るように遅延をかける。
        if (prevFrameEndTime - nowFrameStartTime < 16)
        {
            SDL_Delay(16 - (prevFrameEndTime - nowFrameStartTime));
        }
        
        // SDLが発するイベントの処理を行う
        while (SDL_PollEvent(&e)){
            switch (e.type)
            {
                // ウィンドウが閉じられるとき、、ループを抜ける
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            
            // キー入力状態を管理するマネージャーに渡す。
            KeyManager::Instance()->KeyCheck(e);
        }

        // gameManager側で各オブジェクトが毎フレーム行う処理をさせる。
        gameManager->Update();
        
        // レンダラーを一度クリアしてから描画し、その後に反映させる。
        SDL_RenderClear(mainRenderer);
        gameManager->Redraw();
        SDL_RenderPresent(mainRenderer);
        
        // フレームレート固定のため、フレームの処理がすべて終了した時間を記録する
        prevFrameEndTime = SDL_GetTicks();
    }
    
    return 0;
}
