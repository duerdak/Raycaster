#include <SDL_image.h>
#include "Texture.hpp"

Texture::Texture() : m_surface(nullptr)
{

}

Texture::Texture(const char* filePath, SDL_Window* window) : m_surface(nullptr)
{
    LoadTexture(filePath, window);
}

Texture::Texture(Texture&& obj)
{
    m_surface = obj.m_surface;
    m_width = obj.m_width;
    m_height = obj.m_height;
    obj.m_surface = nullptr;
}

Texture::~Texture()
{
    if (m_surface != nullptr)
    {
        SDL_FreeSurface(m_surface);
    }
}

void Texture::LoadTexture(const char* filePath, SDL_Window* window)
{
    if (window != nullptr)
    {
        m_surface = IMG_Load(filePath);
        if (!m_surface)
        {
            printf("Failed to load %s\n", filePath);
        }
        m_width = m_surface->w;
        m_height = m_surface->h;
    }
}

int Texture::GetWidth()
{
    return m_width;
}

int Texture::GetHeight()
{
    return m_height;
}

SDL_Surface* Texture::GetSurface()
{
    return m_surface;
}