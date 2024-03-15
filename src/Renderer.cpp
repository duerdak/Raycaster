#include "Renderer.hpp"
#include <algorithm>

Renderer::Renderer(SDL_Window* window)
{
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer)
    {
        printf("Failed to create renderer. SDL_Error: %s\n", SDL_GetError());
    }

    SDL_GetWindowSize(window, &m_windowSize.x, &m_windowSize.y);
    m_halfWindowSize = { m_windowSize.x / 2, m_windowSize.y / 2};

    m_colorBuffer = new uint32_t[m_windowSize.x * m_windowSize.y];
    m_colorBufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, m_windowSize.x, m_windowSize.y);

    // Load textures in
    m_wallTextures.push_back(Texture("../../assets/bricks0.png", window));
    m_wallTextures.push_back(Texture("../../assets/bricks1.png", window));
    m_wallTextures.push_back(Texture("../../assets/bricks2.png", window));
    m_ceilTexture.LoadTexture("../../assets/sky-blue.png", window);
    m_floorTexture.LoadTexture("../../assets/grass.png", window);
}

Renderer::~Renderer()
{
    delete[] m_colorBuffer;
    SDL_DestroyTexture(m_colorBufferTexture);
    SDL_DestroyRenderer(m_renderer);
}

void Renderer::BeginDraw()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::EndDraw()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::CastRays(const Player& player, const Map& map)
{
    const int numberOfRays = m_windowSize.x;
    float rayAngle = player.m_angle - (player.m_fieldOfView / 2.0f);
    float incrementAngle = player.m_fieldOfView / numberOfRays;

    m_rays.clear();
    for(int col = 0; col < numberOfRays; col++) // cast a ray for each horizontal column of the screen
    {
        Ray ray(rayAngle);
        ray.CastRay(player, map);
        m_rays.emplace_back(ray);
        rayAngle += incrementAngle;
    }
}

void Renderer::Generate3DView(const Player &player)
{
    for(int x = 0; x < m_windowSize.x; x++)
    {
        float distToProjPlane = m_halfWindowSize.x / tanf(player.m_fieldOfView / 2.0f);
        float correctDistanceToWall = m_rays[x].m_distance * cosf(m_rays[x].m_rayAngle - player.m_angle);
        int sliceHeight = static_cast<int>((1.0f / correctDistanceToWall) * distToProjPlane);

        int wallCeil = static_cast<int>(m_halfWindowSize.y - (sliceHeight / 2.0f)); 
        int wallFloor = static_cast<int>(m_halfWindowSize.y + (sliceHeight / 2.0f));

        for(int y = 0; y < m_windowSize.y; y++)
        {
            if(y < wallCeil)
            {
                float distToCeilPoint = ((player.m_height / (m_halfWindowSize.y - y)) * distToProjPlane) / cosf(m_rays[x].m_rayAngle - player.m_angle);
                glm::vec2 floorPoint(player.m_position.x + cosf(m_rays[x].m_rayAngle) * distToCeilPoint, player.m_position.y + sinf(m_rays[x].m_rayAngle) * distToCeilPoint);
                float sampleX = floorPoint.x - static_cast<int>(floorPoint.x);
                float sampleY = floorPoint.y - static_cast<int>(floorPoint.y);
                uint32_t texel = SampleTexture(sampleX, sampleY, m_ceilTexture);
                m_colorBuffer[(y * m_windowSize.x) + x] = texel;
            }
            else if(y > wallFloor)
            {
                float distToFloorPoint = ((player.m_height / (y - m_halfWindowSize.y)) * distToProjPlane) / cosf(m_rays[x].m_rayAngle - player.m_angle);
                glm::vec2 floorPoint(player.m_position.x + cosf(m_rays[x].m_rayAngle) * distToFloorPoint, player.m_position.y + sinf(m_rays[x].m_rayAngle) * distToFloorPoint);
                float sampleX = floorPoint.x - static_cast<int>(floorPoint.x);
                float sampleY = floorPoint.y - static_cast<int>(floorPoint.y);
                uint32_t texel = SampleTexture(sampleX, sampleY, m_floorTexture);
                m_colorBuffer[(y * m_windowSize.x) + x] = texel;
            }
            else
            {
                float sampleX, sampleY = static_cast<float>(y - wallCeil) / static_cast<float>(wallFloor - wallCeil);
                glm::vec2 blockMidPoint(m_rays[x].m_nHit.x + 0.5f, m_rays[x].m_nHit.y + 0.5f); // the middle point of the hit tile
                float testAngle = atan2f(m_rays[x].m_fHit.y - blockMidPoint.y, m_rays[x].m_fHit.x - blockMidPoint.x); // angle between the m_fHit and the block mid point

                // which side(i.e. quadrant) of the tile has the ray hit
                if(testAngle >= -PI * 0.25f && testAngle < PI * 0.25f)
                {
                    sampleX = m_rays[x].m_fHit.y - m_rays[x].m_nHit.y;
                }
                if(testAngle >= PI * 0.25f && testAngle < PI * 0.75f)
                {
                    sampleX = m_rays[x].m_fHit.x - m_rays[x].m_nHit.x;
                }
                if(testAngle < -PI * 0.25f && testAngle >= -PI * 0.75f)
                {
                    sampleX = m_rays[x].m_fHit.x - m_rays[x].m_nHit.x;
                }
                if(testAngle >= PI * 0.75f || testAngle < -PI * 0.75f)
                {
                    sampleX = m_rays[x].m_fHit.y - m_rays[x].m_nHit.y;
                }

                int textureIndex = m_rays[x].m_wallContent - 1;
                uint32_t texel = SampleTexture(sampleX, sampleY, m_wallTextures[textureIndex]);
                m_colorBuffer[(y * m_windowSize.x) + x] = texel;
            }
        }
    }
}

void Renderer::ClearColorBuffer(uint32_t color)
{
    for (int i = 0; i < m_windowSize.x * m_windowSize.y; i++)
    {
        m_colorBuffer[i] = color;
    }
}

void Renderer::RenderColorBuffer()
{
    // copy the information from the color buffer to the buffer texture
    SDL_UpdateTexture(m_colorBufferTexture, NULL, m_colorBuffer, (int)((uint32_t)(m_windowSize.x) * sizeof(uint32_t)));
    SDL_RenderCopy(m_renderer, m_colorBufferTexture, NULL, NULL);
}

uint32_t Renderer::SampleTexture(float x, float y, Texture& texture)
{
    int sx = std::min(static_cast<int>(x * texture.GetWidth()), texture.GetWidth() - 1);
    int sy = std::min(static_cast<int>(y * texture.GetHeight()), texture.GetHeight() - 1);
    return static_cast<uint32_t*>(texture.GetSurface()->pixels)[(sy * texture.GetWidth()) + sx];
}
