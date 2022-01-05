#ifndef KeyManager_hpp
#define KeyManager_hpp

#include <stdio.h>
#include <SDL2/SDL.h>


/// <summary>
/// キー入力状態をそれぞれのフラグで管理しているクラス。
/// Singleton化しているため、必ずInstance()関数を呼び出した上で使用する。
/// 使用例；if ( KeyInput::Instance()::right )
/// </summary>
class KeyInput
{
    static KeyInput* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    
public:
    bool right, left, up, down = false;         // キー入力があれば対応した変数がtrueになる。

    // SDLのキーイベントを貰い、それに応じてフラグの上げ下げを行う。
    void KeyCheck(SDL_Event e)
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
                }
                break;

        }
    }
    
    // Singleton化しているので、呼び出しのための中継を行う関数。
    static KeyInput* Instance()
    {
        // インスタンスがまだ生成されていなければ、新しく生成して登録する。
        if (instance == NULL)
            instance = new KeyInput();
        
        return instance;
    }
    


};



#endif /* KeyManager_hpp */
