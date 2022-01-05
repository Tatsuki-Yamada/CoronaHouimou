#include "Sprite.hpp"


Sprite::Sprite(int x, int y, string imageName, SDL_Renderer* targetRenderer)
{
    renderer = targetRenderer;
    
    // 画像ファイを読み込む
    string path = "Images/" + imageName + ".bmp";
    SDL_Surface* image = SDL_LoadBMP(path.c_str());
    
    // 画像の透過とテクスチャを作成する
    SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 255, 255));
    texture = SDL_CreateTextureFromSurface(renderer, image);
    
    SDL_FreeSurface(image);
    
    //画像のサイズを取得する
    SDL_QueryTexture(texture, NULL, NULL, &(this->w), &(this->h));
    px = x ; py = y;
    
    reducRatio = 1;
}


Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}


//縮小した上でのwとhを取得する関数
Vector2 Sprite::GetReducSize()
{
    Vector2 size = {int(w * reducRatio), int(h * reducRatio)};
    return size;
}


Vector2 Sprite::GetCenterPos()
{
    Vector2 reducSize = GetReducSize();
    return {px + reducSize.x / 2, py + reducSize.y / 2};
}


void Sprite::SetReducRatio(float ratio)
{
    reducRatio = ratio;
}


// 画面中央に座標を合わせる関数
void Sprite::SetPosToCenter()
{
    int centerX, centerY;
    SDL_GetRendererOutputSize(renderer, &centerX, &centerY);
    centerX /= 2;
    centerY /= 2;
        
    px = centerX;
    py = centerY;
}


void Sprite::Redraw()
{
    Vector2 reducSize = GetReducSize();
    
    SDL_Rect imageRect={0, 0, w, h};
    SDL_Rect drawRect={px - reducSize.x / 2, py - reducSize.y / 2, reducSize.x, reducSize.y};
    
    SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
}


void Sprite::Teleport(int x, int y)
{
    px = x; py = y;
}


void Sprite::Right(int d)
{
    px += d;
}

void Sprite::Left(int d)
{
    Right(-d);
}

void Sprite::Up(int d)
{
    // yのプラス方向は下なので-の値を足している
    py -= d;
}

void Sprite::Down(int d)
{
    Up(-d);
}


// 長方形側のオブジェクトから見て円側のオブジェクトが当たっているかの判定
bool Sprite::CheckHitBoxToCircle(int r, Vector2 centerPos)
{
    Vector2 reducSize = GetReducSize();
    float rootedR = r / sqrt(2);
    
    Vector2 extendLeftUp = {int(px - reducSize.x / 2 - rootedR), int(py - reducSize.y / 2 - rootedR)};
    Vector2 extendRightDown = {int(px + reducSize.x / 2 + rootedR), int(py + reducSize.y / 2 + rootedR)};
    
    if (extendLeftUp.x <= centerPos.x && centerPos.x <= extendRightDown.x)
    {
        if (extendLeftUp.y <= centerPos.y && centerPos.y <= extendRightDown.y)
        {
            return true;
        }
    }
    
    return false;
}


// オブジェクトがマウスに追従する関数
void Sprite::ChaseMouse()
{
    SDL_Point mouse_pos = {0, 0};
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    
    px = mouse_pos.x; py = mouse_pos.y;
}
