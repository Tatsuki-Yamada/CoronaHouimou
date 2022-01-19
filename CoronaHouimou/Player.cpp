#include "Player.hpp"
#include "GameManager.hpp"


// コンストラクタ
Player::Player(int x, int y, SDL_Renderer* targetRenderer) : Sprite(x, y, "Player", targetRenderer)
{
   reducRatio = 0.5;
   r = GetReducSize().x / 2;
}


// 画面の中心に固定する処理が増えるため、SpriteのRedraw()をオーバーライドしている。
void Player::Redraw()
{
    SetPosToCenter();
    
    Vector2 reducSize = GetReducSize();

    SDL_Rect imageRect={0, 0, w, h};
    SDL_Rect drawRect={px - reducSize.x / 2, py - reducSize.y / 2, reducSize.x, reducSize.y};
    SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
}
