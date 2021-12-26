#ifndef Enemy_Cupsule_Orange_hpp
#define Enemy_Cupsule_Orange_hpp

#include <stdio.h>
#include "Enemy.hpp"


class Enemy_Cupsule_Orange : public Enemy
{
public:
    Enemy_Cupsule_Orange(int x, int y, SDL_Renderer* targetRenderer) : Enemy(x, y, string("Enemy_Cupsule_Orange"), targetRenderer){}
    
};




#endif /* Enemy_Cupsule_Orange_hpp */
