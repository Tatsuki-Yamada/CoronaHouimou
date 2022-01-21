#ifndef Text_hpp
#define Text_hpp

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "iostream"
#include "string"


class Text
{
private:
    SDL_Renderer* renderer;         // 描画するレンダラー。

    TTF_Font* font;         // 読み込むフォント。
    SDL_Surface *surface;           // 表示の過程で必要になる変数。
    SDL_Texture *texture;           // 表示の過程で必要になる変数。
    int px, py;         // 表示する座標。
    SDL_Color fontColor;            // 文字の色。
    
public:
    std::string strings;            // 表示する文字列。

    Text(int x, int y, std::string str, int fontSize, SDL_Renderer* targetRenderer, SDL_Color color={0, 0, 0, 255});
    void Redraw();
};


#endif /* Text_hpp */
