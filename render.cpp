#include "render.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>

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
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(const auto &bucket : ps.getParticles())
    {
        for(const auto &particle : bucket)
        {
            float screenY = height - particle.y;
        }
    }
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
    if(texture == nullptr)
    {
        printf("Unable to create texture. Error: %s", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    return success;
}
