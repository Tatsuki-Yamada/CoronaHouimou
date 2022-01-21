#include "Title.hpp"


// コンストラクタ。
Title::Title(SDL_Renderer* targetRenderer)
{
    renderer = targetRenderer;

    titleText = new Text(170, 150, "コロナ包囲網", 50, targetRenderer, {255, 255, 255, 255});
    nameText = new Text(530, 450, "山田 竜暉", 20, targetRenderer, {255, 255, 255, 255});
    clickText = new Text(220, 300, "クリックで開始", 30, targetRenderer, {155, 155, 155, 255});
}


// 描画を行う関数。
void Title::Redraw()
{
    SDL_RenderClear(renderer);
    titleText->Redraw();
    nameText->Redraw();
    clickText->Redraw();
    SDL_RenderPresent(renderer);
}
