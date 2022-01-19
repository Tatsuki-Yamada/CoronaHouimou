#include "Result.hpp"


void Result::Redraw()
{
    SDL_RenderClear(renderer);
    background->Redraw();
    overText->Redraw();
    scoreText->Redraw();
    toTitleText->Redraw();
    SDL_RenderPresent(renderer);
}


void Result::InfoUpdate()
{
    scoreText->strings = "獲得したスコア " + to_string(GameManager::Instance()->score);
}
