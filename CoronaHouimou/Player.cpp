#include "Player.hpp"
#include "GameManager.hpp"


void Player::Redraw()
{
    SetPosToCenter();
    
    Vector2 reducSize = GetReducSize();

    SDL_Rect imageRect={0, 0, w, h};
    SDL_Rect drawRect={px - reducSize.x / 2, py - reducSize.y / 2, reducSize.x, reducSize.y};
    SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
}


void Player::TakeAttack()
{
    GameManager::Instance()->playerHP--;
    GameManager::Instance()->enemyCount--;
    TextManager::Instance()->InfoUpdate();
}
