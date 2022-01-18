#include "Button.hpp"


bool Button::CheckClick()
{
    if (isActive)
    {
        SDL_Point mouse_pos = {0, 0};
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
        
        if (px - w / 2 <= mouse_pos.x && mouse_pos.x <= px + w / 2)
        {
            if (py - h / 2 <= mouse_pos.y && mouse_pos.y <= py + h / 2)
            {
                isActive = false;
                return true;
            }
        }
    }
    return false;
}


void Button::Redraw()
{
    if (isActive)
    {
        Vector2 reducSize = GetReducSize();
        
        SDL_Rect imageRect={0, 0, w, h};
        SDL_Rect drawRect={px - reducSize.x / 2, py - reducSize.y / 2, reducSize.x, reducSize.y};
        
        SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);

        text->Redraw();
    }
}
