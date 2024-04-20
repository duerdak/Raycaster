#pragma once
#include <SDL.h>
#include "Map.hpp"
#include "Player.hpp"

class Ray
{
public:
    Ray(float rayAngle);
    ~Ray();

    void CastRay(const Player& player, const Map& map);

    float m_rayAngle;
    float m_distance;
    glm::vec2 m_fHit;
    glm::ivec2 m_nHit;
    int m_wallContent;
};