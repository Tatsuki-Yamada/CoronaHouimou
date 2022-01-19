#include "Enemy_Cupsule_Orange.hpp"


// コンストラクタ
Enemy_Cupsule_Orange::Enemy_Cupsule_Orange(int x, int y, SDL_Renderer* targetRenderer) : Enemy(x, y, string("Enemy_Cupsule_Orange"), targetRenderer)
{
    reducRatio = 0.2;
}
