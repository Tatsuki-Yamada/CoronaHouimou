#ifndef Aim_hpp
#define Aim_hpp

#include "Sprite.hpp"


class Aim : public Sprite
{
public:
    Aim(SDL_Renderer* targetRenderer);
    void ChaseMouse();

};

#endif /* Aim_hpp */
