#include "render.h"
#include <SDL2/SDL_image.h>
#include <string>

//Renderer:
bool Renderer::Init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize. SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if(window == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n",SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == nullptr)
            {
                printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
        }
    }
    if(!loadColors("assets/color.png")) return false;
    return success;
}
void Renderer::render(const ParticleSystem &ps)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    //renderPoints.clear();
    std::unordered_map<int, std::vector<SDL_Point>> colorGroups;
    int activeCount = 0;
    for(const auto &bucket : ps.getParticles())
    {
        for(const auto &particle : bucket)
        {
            if(particle.isActive)
            {
                activeCount++;
                //renderParticle(particle);
                SDL_Point point;
                point.x = static_cast<int>(particle.x);
                point.y = height - static_cast<int>(particle.y);
                colorGroups[particle.colorindex].push_back(point);
                //renderPoints.push_back(point);
            }
        }
    }
    printf("Active particles: %d\n", activeCount);
    // if(!renderPoints.empty())
    // {
    //     SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    //     SDL_RenderDrawPoints(renderer, renderPoints.data(), renderPoints.size());
    // }
    for(const auto &[colorindex,points] : colorGroups)
    {
        if(points.empty())
        {
            continue;
        }
        SDL_Color color = paletteColors[colorindex];
        SDL_SetRenderDrawColor(renderer,color.r, color.g, color.b, 255);
        SDL_RenderDrawPoints(renderer,points.data(),points.size());
    }
    SDL_RenderPresent(renderer);
}
bool Renderer::loadColors(const std::string filename)
{
    bool success = true;
    SDL_Surface *surface = nullptr;
    surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        printf("Unable to load image. Error: %s",IMG_GetError());
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_LockSurface(surface);
    for(int y = 0; y < 2; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            Uint32 color = ((Uint32*)surface->pixels)[y * surface->w+x];
            Uint8 r,g,b,a;
            SDL_GetRGBA(color,surface->format, &r, &g, &b, &a);
            int colorIndex = y * 10 + x;
            paletteColors[colorIndex] = {r,g,b,a};
        }
    }
    SDL_UnlockSurface(surface);
    //
    // if(texture == nullptr)
    // {
    //     printf("Unable to create texture. Error: %s", SDL_GetError());
    //     return false;
    // }
    // printf("Txture loaded successfully");
    // SDL_FreeSurface(surface);
    return success;
}
// void Renderer::renderParticle(const Particle &particle)
// {
//     if(texture == nullptr)
//     {
//         return;
//     }
//     int row = particle.colorindex/10;
//     int col = particle.colorindex%10;
//     SDL_Rect src;
//     src.x = col;
//     src.y = row;
//     src.w = 1;
//     src.h = 1;
//     int screenY = height - static_cast<int>(particle.y);
//     SDL_Rect dst;
//     dst.x = static_cast<int>(particle.x);
//     dst.y = screenY;
//     dst.w = 1;
//     dst.h = 1;

    //SDL_RenderCopy(renderer, texture, &src, &dst);
//}
bool Renderer::isRunning()
{
    bool isRunning = true;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return isRunning;
}
Renderer::~Renderer()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
