#include "Button.hpp"


//コンストラクタ。
Button::Button(Vector2 pos, const char* buttonType, const char* str, SDL_Renderer* targetRenderer) : Sprite(pos.x, pos.y, buttonType, targetRenderer)
{
    renderer = targetRenderer;
    text = new Text(pos.x - w / 4, pos.y, str, 20, targetRenderer, {255, 255, 255, 255});
    isActive = false;
}


// クリックされた座標がボタンの上にあるか判定する関数。
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


// 描画する関数。
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
