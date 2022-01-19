#include "TextManager.hpp"


TextManager* TextManager::instance = nullptr;


void TextManager::Init()
{
    scoreText = new Text(50, 50, "スコア 0", 20, inGameRenderer);
    enemyCountText = new Text(500, 50, "敵 残り10体", 20, inGameRenderer);
    lifeText = new Text(500, 80, "ライフ 5", 20, inGameRenderer);
}


void TextManager::Redraw()
{
    scoreText->Redraw();
    enemyCountText->Redraw();
    lifeText->Redraw();
}


void TextManager::InfoUpdate()
{
    std::string s = to_string(GameManager::Instance()->score);
    scoreText->strings = "スコア " + s;
    std::string e = to_string(GameManager::Instance()->enemyCount);
    enemyCountText->strings = "敵 残り" + e + "体";
    std::string h = to_string(GameManager::Instance()->playerHP);
    lifeText->strings = "ライフ " + h;
}
