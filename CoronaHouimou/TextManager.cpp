#include "TextManager.hpp"


TextManager* TextManager::instance = nullptr;


void TextManager::Init()
{
    scoreText = new Text(50, 50, "0000", 20, inGameRenderer);
}


void TextManager::Redraw()
{
    scoreText->Redraw();
}
