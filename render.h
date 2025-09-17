#pragma once
#include <SDL2/SDL.h>
#include <array>
#include <unordered_map>
#include "particlesystem.h"
class Renderer
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int width, height;
    bool initialize;
    std::array<SDL_Color,10> firecolors;
    std::array<SDL_Color,10> raincolors;
    bool loadColors(const std::string filename);
    //void renderParticle(const Particle &particle);
    std::vector <SDL_Point> renderPoints;
    std::unordered_map<int, SDL_Color> paletteColors;
public:
    Renderer(int a,int b): width(a),height(b){}
    ~Renderer();
    bool Init();
    void render(const ParticleSystem &ps);
    bool isRunning();
};
