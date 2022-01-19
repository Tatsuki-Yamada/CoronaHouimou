#include "Tutorial.hpp"


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
