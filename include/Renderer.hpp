#pragma once
#include <SDL.h>
#include <vector>
#include "Ray.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Texture.hpp"

class Renderer
{
    public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void BeginDraw();
    void EndDraw();

    /// @brief Cast rays and store them in m_rays
    void CastRays(const Player& player, const Map& map);

    /// @brief Generate the 3D view/projection by filling the color buffer with the appropriate pixels 
    void Generate3DView(const Player& player);

    /// @brief Fill the color buffer with a uint32_t color
    /// @param color
    void ClearColorBuffer(uint32_t color);

    /// @brief Update the color buffer texture with the pixels of the screen array
    void RenderColorBuffer();

    private:
    /// @brief Pass in coordinates in [0 - 1] range to sample a color from a texture
    /// @return A uint32_t color
    uint32_t SampleTexture(float x, float y, Texture& texture);

    SDL_Renderer *m_renderer;

    // array for storing the screen pixels
    uint32_t* m_colorBuffer;

    // texture to render on the screen
    SDL_Texture* m_colorBufferTexture;

    // Stores the cast rays
    std::vector<Ray> m_rays;

    std::vector<Texture> m_wallTextures;
    Texture m_ceilTexture;
    Texture m_floorTexture;

    glm::ivec2 m_windowSize;
    glm::ivec2 m_halfWindowSize;
};