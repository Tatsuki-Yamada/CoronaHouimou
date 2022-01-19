
#ifndef Player_hpp
#define Player_hpp

#include "Sprite.hpp"


class Player : public Sprite
{
public:
    int r;
    
    Player(int x, int y, SDL_Renderer* targetRenderer);
    void Redraw();
};


#endif /* Player_hpp */
