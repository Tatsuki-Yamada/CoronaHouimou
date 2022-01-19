#ifndef Result_hpp
#define Result_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"
#include "Background.hpp"
#include "GameManager.hpp"
#include "string"



class Result
{
private:
    Background* background;
    Text* overText;
    Text* scoreText;
    Text* toTitleText;
    
    SDL_Renderer* renderer;
    
public:
    Result(SDL_Renderer* targetRenderer)
    {
        renderer = targetRenderer;
        
        background = new Background(targetRenderer);
        overText = new Text(100, 100, "ゲームオーバー", 40, targetRenderer);
        scoreText = new Text(100, 300, "獲得したスコア ", 30, targetRenderer);
        toTitleText = new Text(100, 350, "Returnキーでタイトルへ", 30, targetRenderer, {100, 100, 100, 255});
    }
    
    void Redraw();
    void InfoUpdate();
};

#endif /* Result_hpp */
