#ifndef Title_hpp
#define Title_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"


class Title
{
private:
    SDL_Renderer* renderer;         // 描画するレンダラー。

    Text* titleText;            // ゲームタイトルのテキスト。
    Text* nameText;         // 作者名のテキスト。
    Text* clickText;            // クリックして開始 のテキスト
    
    
public:
    Title(SDL_Renderer* targetRenderer);
    void Redraw();
};

#endif /* Title_hpp */
