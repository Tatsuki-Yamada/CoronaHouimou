
#ifndef Player_hpp
#define Player_hpp

#include "Sprite.hpp"

// Playerクラス
class Player : public Sprite
{    
public:
    Player(int x, int y, SDL_Renderer* targetRenderer) : Sprite(x, y, "Player", targetRenderer)
    {
        ChangeReducRatio(0.5);
    }
    
    void Redraw();
    void ChaseMouse();
};


#endif /* Player_hpp */
