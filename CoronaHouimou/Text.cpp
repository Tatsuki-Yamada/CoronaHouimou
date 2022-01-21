#include "Text.hpp"


// コンストラクタ。
Text::Text(int x, int y, std::string str, int fontSize, SDL_Renderer* targetRenderer, SDL_Color color)
{
    px = x;
    py = y;
    strings = str;
    font = TTF_OpenFont("Fonts/komorebi-gothic.ttf", fontSize);
    fontColor = color;

    if (font == nullptr)
    {
        std::cout << "font error" << std::endl;
    }
    renderer = targetRenderer;
}


// 描画する関数。
void Text::Redraw()
{
    surface = TTF_RenderUTF8_Blended(font, strings.c_str(), fontColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int iw,ih;
    SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);

    SDL_Rect txtRect = {0,0,iw,ih};
    SDL_Rect pasteRect = {px,py,iw,ih};

    SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
}
