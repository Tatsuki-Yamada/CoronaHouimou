#ifndef Result_hpp
#define Result_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"
#include "Background.hpp"
#include "GameManager.hpp"
#include "string"


class Result
{
private:
    SDL_Renderer* renderer;         // 描画するレンダラー。

    Background* background;         // 背景画像のオブジェクト。
    Text* overText;         // ゲームオーバーのテキスト。
    Text* scoreText;            // スコアのテキスト。
    Text* toTitleText;          // タイトルへ のテキスト。
    
    
public:
    Result(SDL_Renderer* targetRenderer);
    void Redraw();
    void InfoUpdate();
};

#endif /* Result_hpp */
