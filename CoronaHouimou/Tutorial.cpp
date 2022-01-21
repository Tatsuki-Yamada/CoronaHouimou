#include "Tutorial.hpp"


// コンストラクタ。
Tutorial::Tutorial(SDL_Renderer* targetRenderer)
{
    renderer = targetRenderer;
    
    tutorialText = new Text(30, 100, "ゲーム説明", 30, targetRenderer, {255, 255, 255, 255});
    firstText = new Text(30, 200, "・マウスで狙い、Spaceキー長押しで弾を連射、薬は敵だ、倒せ！", 20, targetRenderer, {255, 255, 255, 255});
    secondText = new Text(30, 250, "・WASDで移動し、薬から逃げろ！", 20, targetRenderer, {255, 255, 255, 255});
    thirdText = new Text(30, 300, "・薬を全滅させると変異ができる。マウスクリックで1つ選択だ！", 20, targetRenderer, {255, 255, 255, 255});
    toStartText = new Text(30, 400, "Spaceキーでゲーム開始", 30, targetRenderer, {155, 155, 155, 255});

}


// 描画を行う関数。
void Tutorial::Redraw()
{
    SDL_RenderClear(renderer);
    tutorialText->Redraw();
    firstText->Redraw();
    secondText->Redraw();
    thirdText->Redraw();
    toStartText->Redraw();
    SDL_RenderPresent(renderer);
}
