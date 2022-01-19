#include "Title.hpp"


void Title::Redraw()
{
    SDL_RenderClear(renderer);
    titleText->Redraw();
    nameText->Redraw();
    clickText->Redraw();
    SDL_RenderPresent(renderer);
}
