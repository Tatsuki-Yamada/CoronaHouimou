#ifndef KeyManager_hpp
#define KeyManager_hpp

#include <SDL2/SDL.h>


class KeyManager
{
    static KeyManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。
    
public:
    bool right, left, up, down, space, enter = false;         // キー入力があれば対応した変数がtrueになる。
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
