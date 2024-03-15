#include "Ray.hpp"

Ray::Ray(float rayAngle) : m_rayAngle(rayAngle)
{

}

Ray::~Ray()
{

}

void Ray::CastRay(const Player& player, const Map& map)
{
    glm::vec2 rayStart = player.m_position;
    glm::vec2 rayDir(cosf(m_rayAngle), sinf(m_rayAngle));
    glm::vec2 rayUnitStepSize(sqrtf(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)), sqrtf(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y)));
    glm::ivec2 mapCheck(rayStart);
    glm::vec2 rayLength1D;
    glm::ivec2 gridStep;

    // Check if the ray is going left or right. Calculate the ray length in the x dimension to the first grid intersection.
    if(rayDir.x < 0)
    {
        gridStep.x = -1;
        rayLength1D.x = (rayStart.x - mapCheck.x) * rayUnitStepSize.x;
    }
    else
    {
        gridStep.x = 1;
        rayLength1D.x = ((mapCheck.x + 1) - rayStart.x) * rayUnitStepSize.x;
    }

    // Check if the ray is going up or down. Calculate the ray length in the y dimension to the first grid intersection.
    if(rayDir.y < 0)
    {
        gridStep.y = -1;
        rayLength1D.y = (rayStart.y - mapCheck.y) * rayUnitStepSize.y;
    }
    else
    {
        gridStep.y = 1;
        rayLength1D.y = ((mapCheck.y + 1) - rayStart.y) * rayUnitStepSize.y;
    }

    bool tileFound = false;
    float distance = 0.0f;
    while(!tileFound)
    {
        if(rayLength1D.x < rayLength1D.y)
        {
            mapCheck.x += gridStep.x;
            distance = rayLength1D.x;
            rayLength1D.x += rayUnitStepSize.x;
        }
        else
        {
            mapCheck.y += gridStep.y;
            distance = rayLength1D.y;
            rayLength1D.y += rayUnitStepSize.y;
        }

        if(mapCheck.x >= 0 && mapCheck.x < map.GetSize().x && mapCheck.y >= 0 && mapCheck.y < map.GetSize().y)
        {
            if(map.GetMap()[mapCheck.y][mapCheck.x] != 0)
            {
                tileFound = true;
                m_distance = distance;
                m_fHit = rayStart + rayDir * distance;
                m_nHit = mapCheck;
                m_wallContent = map.GetMap()[mapCheck.y][mapCheck.x];
            }
        }
    }
}