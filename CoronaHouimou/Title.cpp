#include "Title.hpp"


void Title::Redraw()
{
    SDL_RenderClear(renderer);
    titleText->Redraw();
    nameText->Redraw();
    SDL_RenderPresent(renderer);
}
