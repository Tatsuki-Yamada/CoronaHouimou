#ifndef Tutorial_hpp
#define Tutorial_hpp

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "Text.hpp"
#include "Background.hpp"
#include "GameManager.hpp"
#include "string"



class Tutorial
{
private:
    Text* tutorialText;
    Text* firstText;
    Text* secondText;
    Text* thirdText;
    Text* toStartText;
    
    SDL_Renderer* renderer;
    
public:
    Tutorial(SDL_Renderer* targetRenderer)
    {
        renderer = targetRenderer;
        
        tutorialText = new Text(30, 100, "ゲーム説明", 30, targetRenderer, {255, 255, 255, 255});
        firstText = new Text(30, 200, "・マウスで狙い、Spaceキー長押しで弾を連射、薬を倒せ！", 20, targetRenderer, {255, 255, 255, 255});
        secondText = new Text(30, 250, "・WASDで移動し、薬から逃げろ！", 20, targetRenderer, {255, 255, 255, 255});
        thirdText = new Text(30, 300, "・薬を全滅させると変異ができる。マウスクリックで1つ選択だ！", 20, targetRenderer, {255, 255, 255, 255});
        toStartText = new Text(30, 400, "Spaceキーでゲーム開始", 30, targetRenderer, {155, 155, 155, 255});

    }
    
    void Redraw();
};
#endif /* Tutorial_hpp */
