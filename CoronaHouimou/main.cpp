#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


// 初期化をまとめた関数
bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        cout << "SDL_Init failed.";
        return false;
    }

    window = SDL_CreateWindow("WindowName",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    
    return true;
}


// スプライトクラス
class Sprite
{
    SDL_Texture* texture;
    int px, py, w, h;
    
public:
    Sprite(int x, int y, string imageName){
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
    }

    ~Sprite(){
        SDL_DestroyTexture(texture);
    }
    
    void redraw(){
        SDL_Rect imageRect={0,0,w,h};
        SDL_Rect drawRect={px,py,w,h};
        SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
    }
    
    void forward(int d){
        px = px + d;
    }
    
};

int main(int argc, const char * argv[]) {
    
    if (!Init())
        return -1;
    
    Sprite* sprite = new Sprite(0, 0, "Player");
    
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
        SDL_RenderClear(renderer);

        sprite->forward(1);
        sprite->redraw();
        SDL_RenderPresent(renderer);
     }
    
    return 0;
}
