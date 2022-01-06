#ifndef KeyManager_hpp
#define KeyManager_hpp

#include <stdio.h>
#include <SDL2/SDL.h>


/// <summary>
/// キー入力状態をそれぞれのフラグで管理しているクラス。
/// Singleton化しているため、必ずInstance()関数を呼び出した上で使用する。
/// 使用例；if ( KeyInput::Instance()::right )
/// </summary>
class KeyManager
{
    static KeyManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    
public:
    bool right, left, up, down, space = false;         // キー入力があれば対応した変数がtrueになる。
    bool leftClick = false;         // クリック入力があれば対応した変数がtrueになる。


    
    void KeyCheck(SDL_Event e);
    
    // Singleton化しているので、呼び出しのための中継を行う関数。
    static KeyManager* Instance()
    {
        // インスタンスがまだ生成されていなければ、新しく生成して登録する。
        if (instance == NULL)
            instance = new KeyManager();
        
        return instance;
    }
    


};



#endif /* KeyManager_hpp */
