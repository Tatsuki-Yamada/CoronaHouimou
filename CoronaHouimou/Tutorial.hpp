#ifndef Tutorial_hpp
#define Tutorial_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"
#include "Background.hpp"
#include "GameManager.hpp"
#include "string"


class Tutorial
{
private:
    SDL_Renderer* renderer;         // 描画するレンダラー。

    Text* tutorialText;         // ゲーム説明 のテキスト。
    Text* firstText;            // 1行目のテキスト。
    Text* secondText;           // 2行目のテキスト。
    Text* thirdText;            // 3行目のテキスト
    Text* toStartText;          // Spaceで開始 のテキスト。
    
public:
    Tutorial(SDL_Renderer* targetRenderer);
    void Redraw();
};
#endif /* Tutorial_hpp */
