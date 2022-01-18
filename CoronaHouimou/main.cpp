#include <iostream>
#include <SDL2/SDL.h>


#include "GameManager.hpp"
#include "Title.hpp"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL;


enum WindowState
{
    TitleWindow,
    InGame,
    ResultWindow
};

// SDL周りの初期化をまとめて行う関数。
bool Init()
{
    // 初期化に失敗したらfalseを返す。
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << "SDL_Init failed." << endl;
        return false;
    }
    
    if (TTF_Init())
    {
        cout << "TTF_Init failed." << endl;
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

    // タイトル画面を表示するオブジェクトを生成する。
    Title* title = new Title(mainRenderer);

    
    // ゲームマネージャーを生成する。
    GameManager::Instance()->inGameRenderer = mainRenderer;
    GameManager::Instance()->GameStart();
    
    // 弾のマネージャーにレンダラーを設定する。
    BulletManager::Instance()->inGameRenderer = mainRenderer;
    
    EnemyManager::Instance()->inGameRenderer = mainRenderer;
    EnemyManager::Instance()->CreateSpawners();
    
    TextManager::Instance()->inGameRenderer = mainRenderer;
    TextManager::Instance()->Init();
    
    // フレームレートを調整する為の変数を生成する。
    int prevFrameEndTime = 0, nowFrameStartTime;

    // メインループで使う変数を生成する。
    SDL_Event e;
    bool quit = false;
    WindowState windowState = TitleWindow;
    
    
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
        
        
        // 画面の遷移状態によって、描画するものを変える。
        switch (windowState)
        {
            //タイトル画面
            case TitleWindow:
                title->Redraw();
                
                if (KeyManager::Instance()->leftClick)
                    windowState = InGame;

                break;
                
            // ゲーム中
            case InGame:
                // gameManager側で各オブジェクトが毎フレーム行う処理をさせる。
                GameManager::Instance()->Update();
                
                // レンダラーを一度クリアしてから描画し、その後に反映させる。
                SDL_RenderClear(mainRenderer);
                GameManager::Instance()->Redraw();
                SDL_RenderPresent(mainRenderer);
                

                break;
                
            // リザルト画面
            case ResultWindow:
                break;
                
        }
        
        // フレームレート固定のため、フレームの処理がすべて終了した時間を記録する
        prevFrameEndTime = SDL_GetTicks();
    }
    
    delete KeyManager::Instance();
    delete GameManager::Instance();
    delete BulletManager::Instance();
    delete EnemyManager::Instance();
    delete TextManager::Instance();
    
    return 0;
}
