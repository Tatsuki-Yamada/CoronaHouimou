#include "Aim.hpp"


// コンストラクタ。
Aim::Aim(SDL_Renderer* targetRenderer) : Sprite(0, 0, "Aim", targetRenderer)
{
    reducRatio = 0.2;
}


// オブジェクトがマウスに追従する関数
void Aim::ChaseMouse()
{
    SDL_Point mouse_pos = {0, 0};
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    
    px = mouse_pos.x; py = mouse_pos.y;
}
