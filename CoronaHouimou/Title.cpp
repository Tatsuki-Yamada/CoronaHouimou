#include "Title.hpp"


void Title::Redraw()
{
    //TTF_SetFontOutline(font, 1);//枠抜きで描写するとき
    surface = TTF_RenderUTF8_Blended(font, "コロナ包囲網", (SDL_Color){255,255,255,255});

    //surfaceからTextureを作る
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //文字を描写したTextureのサイズを取得する
    int iw,ih;
    SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);

    SDL_Rect txtRect = {0,0,iw,ih};
    SDL_Rect pasteRect = {200,200,iw,ih};

    //Textureを描写する
    //描写元の描写する部分,描写先の描写する部分)
    //サイズが違うと勝手にTextureを伸展してくれる
    SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
    //windowにレンダリングする
    SDL_RenderPresent(renderer);
}
