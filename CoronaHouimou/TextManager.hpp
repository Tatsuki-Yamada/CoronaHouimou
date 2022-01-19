#ifndef TextManager_hpp
#define TextManager_hpp

#include <stdio.h>
#include "SDL2/SDL.h"
#include "Text.hpp"
#include "string"
#include "GameManager.hpp"


class TextManager
{
private:
    static TextManager* instance;          // Singleton化のため、一度生成したインスタンスを保存する変数。

    
public:
    SDL_Renderer* inGameRenderer;
    Text* scoreText;
    Text* enemyCountText;
    Text* lifeText;
    
    void Init();
    void Redraw();
    void InfoUpdate();
    
    // Singleton化しているので、呼び出しのための中継を行う関数。
    static TextManager* Instance()
    {
        // インスタンスがまだ生成されていなければ、新しく生成して登録する。
        if (instance == NULL)
            instance = new TextManager();
        
        return instance;
    }
};

#endif /* TextManager_hpp */
