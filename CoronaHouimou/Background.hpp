#ifndef Background_hpp
#define Background_hpp

#include "Sprite.hpp"


class Background : public Sprite
{
public:
    Background(SDL_Renderer* targetRenderer);
    void Redraw();
};

#endif /* Background_hpp */
