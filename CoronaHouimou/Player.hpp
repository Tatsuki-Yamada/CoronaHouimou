
#ifndef Player_hpp
#define Player_hpp

#include "Sprite.hpp"

// Playerクラス
class Player : public Sprite
{    
public:
    int r;
    
    Player(int x, int y, SDL_Renderer* targetRenderer) : Sprite(x, y, "Player", targetRenderer)
    {
        ChangeReducRatio(0.5);
        r = GetReducSize().x / 2;
        cout << r;
    }
    
    void Redraw();
    void ChaseMouse();
    Vector2 GetPos();
    Vector2 GetCenterPos();
};


#endif /* Player_hpp */
