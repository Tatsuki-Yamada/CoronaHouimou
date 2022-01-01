#include "Player.hpp"

// マウス追従を試すときはこの定数をfalseにする
#define RENDER_TO_CENTER true


void Player::Redraw()
{
#if RENDER_TO_CENTER
    SetPosToCenter();
#endif
    
    Vector2 reducSize = GetReducSize();

    SDL_Rect imageRect={0, 0, w, h};
    SDL_Rect drawRect={px - reducSize.x / 2, py - reducSize.y / 2, reducSize.x, reducSize.y};
    SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
}


// プレイヤーがマウスに追従する関数
void Player::ChaseMouse()
{
    SDL_Point mouse_pos = {0, 0};
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    
    px = mouse_pos.x; py = mouse_pos.y;
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
