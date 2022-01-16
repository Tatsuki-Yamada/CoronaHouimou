#include "Button.hpp"


bool Button::CheckClick()
{
    if (isActive)
    {
        SDL_Point mouse_pos = {0, 0};
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
        
        if (leftUp.x <= mouse_pos.x && mouse_pos.x <= leftUp.x + size.x)
        {
            if (leftUp.y <= mouse_pos.y && mouse_pos.y <= leftUp.y + size.y)
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
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_Rect faceRect = {leftUp.x, leftUp.y, size.x, size.y};
        SDL_RenderFillRect(renderer, &faceRect);
    }
}
