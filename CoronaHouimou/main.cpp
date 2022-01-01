#include <iostream>
#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Enemy_Cupsule_Orange.hpp"
#include "Background.hpp"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* mainRenderer = NULL;

int playerMoveSpeed = 3;


// 初期化をまとめた関数
bool Init()
{
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


// Singleton化したキー入力を取るクラス
class KeyInput
{
    static KeyInput* instance;
    
public:
    bool right, left, up, down = false;

    void KeyCheck(SDL_Event e)
    {
        switch (e.type)
        {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        right = true;
                        break;
                    case SDLK_LEFT:
                        left = true;
                        break;
                    case SDLK_UP:
                        up = true;
                        break;
                    case SDLK_DOWN:
                        down = true;
                        break;
                }
                break;
                
            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        right = false;
                        break;
                    case SDLK_LEFT:
                        left = false;
                        break;
                    case SDLK_UP:
                        up = false;
                        break;
                    case SDLK_DOWN:
                        down = false;
                        break;
                }
                break;

        }
    }
    
    static KeyInput* Instance()
    {
        if (instance == NULL)
            instance = new KeyInput();
        
        return instance;
    }
};

KeyInput* KeyInput::instance = NULL;

// メイン関数
int main(int argc, const char * argv[])
{
    // SDLの初期化を行う
    if (!Init())
        return -1;
    
    
    Player* player = new Player(0, 0, mainRenderer);
    Enemy_Cupsule_Orange* orange = new Enemy_Cupsule_Orange(5, 5, mainRenderer);
    Background* background = new Background(mainRenderer);
    
    
    // フレームレートを調整する為の変数
    int prevFrameEndTime = 0, nowFrameStartTime;
        
    // メインループ
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        // フレームの処理が始まった時間を取得する
        nowFrameStartTime = SDL_GetTicks();
        
        // 前フレームと今フレームの時間を見て、差が16ミリ秒以内の場合は16ミリ秒の差が出るように調整する
        if (prevFrameEndTime - nowFrameStartTime < 16)
        {
            SDL_Delay(16 - (prevFrameEndTime - nowFrameStartTime));
        }
        
        // イベントの処理を行う
        while (SDL_PollEvent(&e)){
            switch (e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            
            KeyInput::Instance()->KeyCheck(e);
        }
        
        // キー入力状態に応じた処理を行う
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
        
        orange->MoveToPlayer(player->GetPos());
        
        if (orange->CheckHitBoxToCircle(player->r, player->GetCenterPos()))
            orange->Teleport(10, 10);
        
        
        SDL_RenderClear(mainRenderer);

        background->Redraw();
        player->Redraw();
        orange->Redraw();
        
        SDL_RenderPresent(mainRenderer);
        
        // フレームの処理がすべて終了した時間を記録する
        prevFrameEndTime = SDL_GetTicks();
    }
    
    return 0;
}
