
#ifndef Player_hpp
#define Player_hpp

#include "Sprite.hpp"

// Playerクラス
class Player : public Sprite
{
private:
    int hp = 5;
    
public:
    int r;

    
    Player(int x, int y, SDL_Renderer* targetRenderer) : Sprite(x, y, "Player", targetRenderer)
    {
        SetReducRatio(0.5);
        r = GetReducSize().x / 2;
    }
    
    void Redraw();
    void TakeAttack();
};


#endif /* Player_hpp */
