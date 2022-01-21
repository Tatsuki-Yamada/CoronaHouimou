#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "iostream"

using namespace std;


// x成分とy成分を持つ構造体。
struct Vector2
{
    int x;
    int y;
};


class Sprite
{
protected:
    SDL_Renderer* renderer = NULL;          // 描画先のレンダラー。
    SDL_Texture* texture;           // 画像から作ったテクスチャを保存する。
    int px, py;         // 描画位置の変数。この位置に画像の中央が来るようにしている。
    int w, h;           // 画像の縦横のサイズ。
    float reducRatio;           // 画像の縮小度合い。
    
public:
    bool isActive = true;           // オブジェクトの有効・無効を示す。

    Sprite(int x, int y, string imageName, SDL_Renderer* targetRenderer);
    ~Sprite();
    Vector2 GetReducSize();
    Vector2 GetPos();
    void SetPosToCenter();
    void Redraw();
    void Teleport(int x, int y);
    void Right(int d, bool divR2 = false);
    void Left(int d, bool divR2 = false);
    void Up(int d, bool divR2 = false);
    void Down(int d, bool divR2 = false);
};


#endif /* Sprite_hpp */
