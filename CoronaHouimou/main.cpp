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

    window = SDL_CreateWindow("コロナ包囲網",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);
    
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
    Sprite(int x, int y, string imageName)
    {
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

    ~Sprite()
    {
        SDL_DestroyTexture(texture);
    }
    
    void Redraw()
    {
        SDL_Rect imageRect={0, 0, w, h};
        SDL_Rect drawRect={px, py, w, h};
        SDL_RenderCopy(renderer, texture, &imageRect, &drawRect);
    }
    
    void Forward(int d)
    {
        px += d;
    }
    
    void Up(int d)
    {
        // yのプラス方向は下なので-の値を足している
        py -= d;
    }
};


// Playerクラス
class Player : public Sprite
{
public:
    Player(int x, int y) : Sprite(x, y, "Player")
    {
        
    }
};


// Singleton化したキー入力を取るクラス
class KeyInput
{
    static KeyInput* instance;
    
public:
    bool right, left, up, down = false;

    void KeyCheck(SDL_Event e)
    {
        switch (e.type)
        {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        right = true;
                        break;
                    case SDLK_LEFT:
                        left = true;
                        break;
                    case SDLK_UP:
                        up = true;
                        break;
                    case SDLK_DOWN:
                        down = true;
                        break;
                }
                break;
                
            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        right = false;
                        break;
                    case SDLK_LEFT:
                        left = false;
                        break;
                    case SDLK_UP:
                        up = false;
                        break;
                    case SDLK_DOWN:
                        down = false;
                        break;
                }
                break;

        }
    }
    
    static KeyInput* Instance()
    {
        if (instance == NULL)
            instance = new KeyInput();
        
        return instance;
    }
};

KeyInput* KeyInput::instance = NULL;

// メイン関数
int main(int argc, const char * argv[])
{
    // SDLの初期化を行う
    if (!Init())
        return -1;
    
    
    Player* player = new Player(0, 0);
    
    // メインループ
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            switch (e.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            
            KeyInput::Instance()->KeyCheck(e);
        }
        
        // キー入力状態に応じた処理を行う
        if (KeyInput::Instance()->right)
            player->Forward(5);
        if (KeyInput::Instance()->left)
            player->Forward(-5);

        
        SDL_RenderClear(renderer);

        player->Redraw();
        SDL_RenderPresent(renderer);
    }
    
    return 0;
}
