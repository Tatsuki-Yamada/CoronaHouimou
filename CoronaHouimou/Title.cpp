#include "Title.hpp"


void Title::Redraw()
{
    nameText->Redraw();
    //windowにレンダリングする
    SDL_RenderPresent(renderer);
}
