#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "iostream"

using namespace std;


struct Vector2
{
    int x;
    int y;
};


class Sprite
{
protected:
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture;
    int px, py;
    int w, h;
    float reducRatio;
    
public:
    Sprite(int x, int y, string imageName, SDL_Renderer* targetRenderer);
    ~Sprite();
    
    Vector2 GetReducSize();
    Vector2 GetPos();
    void SetReducRatio(float ratio);
    void SetPosToCenter();
    void Redraw();
    void Teleport(int x, int y);
    void Right(int d, bool divR2 = false);
    void Left(int d, bool divR2 = false);
    void Up(int d, bool divR2 = false);
    void Down(int d, bool divR2 = false);
    bool CheckHitRectToCircle(int r, Vector2 CenterPos);
    void ChaseMouse();
};


#endif /* Sprite_hpp */
