#ifndef Button_hpp
#define Button_hpp

#include <SDL2/SDL.h>
#include "Sprite.hpp"
#include "Text.hpp"


class Button : public Sprite
{
private:
    Text* text;
    
public:
    SDL_Renderer* renderer = nullptr;
        
    Button(Vector2 pos, const char* buttonType, const char* str, SDL_Renderer* targetRenderer);
    bool CheckClick();
    void Redraw();
};

#endif /* Button_hpp */
