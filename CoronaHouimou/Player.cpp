#include "Player.hpp"


void Player::Redraw()
{
    SetPosToCenter();
    
    Vector2 reducSize = GetReducSize();

    SDL_Rect imageRect={0, 0, w, h};
    SDL_Rect drawRect={px - reducSize.x / 2, py - reducSize.y / 2, reducSize.x, reducSize.y};
    SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
}


Vector2 Player::GetPos()
{
    Vector2 v = {px, py};
    return v;
}


// playerはpxとpyが中心になるよう設定されているため、そのまま返すようにする。
Vector2 Player::GetCenterPos()
{
    return GetPos();
}
