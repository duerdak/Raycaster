#pragma once
#include <SDL.h>

class Texture
{
    public:
    Texture();
    Texture(const char* filePath, SDL_Window* window);
    Texture(Texture&& obj);
    ~Texture();

    void LoadTexture(const char* filePath, SDL_Window* window);

    int GetWidth();
    int GetHeight();
    SDL_Surface* GetSurface();

    private:
    SDL_Surface* m_surface;
    int m_width;
    int m_height;
};