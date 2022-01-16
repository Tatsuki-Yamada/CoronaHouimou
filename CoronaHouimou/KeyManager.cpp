#include "KeyManager.hpp"


KeyManager* KeyManager::instance = nullptr;


// SDLのキーイベントを貰い、それに応じてフラグの上げ下げを行う。
void KeyManager::KeyCheck(SDL_Event e)
{
    switch (e.type)
    {
        // キーを押した状態にするエリア
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
                case SDLK_RIGHT:
                case SDLK_d:
                    right = true;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    left = true;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    up = true;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    down = true;
                    break;
                case SDLK_SPACE:
                    space = true;
                    break;
            }
            break;
            
        // キーを離した状態にするエリア
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
                case SDLK_RIGHT:
                case SDLK_d:
                    right = false;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    left = false;
                    break;
                case SDLK_UP:
                case SDLK_w:
                    up = false;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    down = false;
                    break;
                case SDLK_SPACE:
                    space = false;
            }
            break;

        // マウスボタンを押した状態にするエリア
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT)
                leftClick = true;
            break;
            
        // マウスボタンを離した状態にするエリア
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT)
                leftClick = false;
            break;
        
    }
}
