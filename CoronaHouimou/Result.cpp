#include "Result.hpp"


// コンストラクタ。
Result::Result(SDL_Renderer* targetRenderer)
{
    renderer = targetRenderer;
    
    background = new Background(targetRenderer);
    overText = new Text(100, 100, "ゲームオーバー", 40, targetRenderer);
    scoreText = new Text(100, 300, "獲得したスコア ", 30, targetRenderer);
    toTitleText = new Text(100, 350, "Returnキーでタイトルへ", 30, targetRenderer, {100, 100, 100, 255});
}


// 描画を行う関数。
void Result::Redraw()
{
    SDL_RenderClear(renderer);
    background->Redraw();
    overText->Redraw();
    scoreText->Redraw();
    toTitleText->Redraw();
    SDL_RenderPresent(renderer);
}


// テキストの情報更新を行う関数。
void Result::InfoUpdate()
{
    scoreText->strings = "獲得したスコア " + to_string(GameManager::Instance()->score);
}
