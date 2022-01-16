#ifndef Title_hpp
#define Title_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>



class Title
{
private:
    TTF_Font* font;
    SDL_Surface *surface;
    SDL_Texture *texture;
    
    SDL_Renderer* renderer;
    
public:
    Title(SDL_Renderer* targetRenderer)
    {
        renderer = targetRenderer;

        font = TTF_OpenFont("Fonts/komorebi-gothic.ttf", 40);
        
        if (!font)
        {
            std::cout << "font load error." << std::endl;
        }
    }
    
    void Redraw();
};

#endif /* Title_hpp */
