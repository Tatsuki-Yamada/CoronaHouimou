#include "Background.hpp"


// コンストラクタ。
Background::Background(SDL_Renderer* targetRenderer) : Sprite(320, 240, "Background", targetRenderer)
{
    reducRatio = 2.5;
    SetPosToCenter();
}


//
void Background::Redraw()
{
    Vector2 reducSize = GetReducSize();
    
    SDL_Rect imageRect={0, 0, w, h};
    
    // タイルを複数枚繋げて表示するためのループ
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            int offsetX = reducSize.x * x;
            int offsetY = reducSize.y * y;

            SDL_Rect drawRect={px - reducSize.x / 2 + offsetX, py - reducSize.y / 2 + offsetY, reducSize.x, reducSize.y};
            SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
        }
    }
    
}

