#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <SDL.h>

class Map
{
public:
    Map(std::vector<std::vector<int>> map);

    const std::vector<std::vector<int>>& GetMap() const;
    glm::ivec2 GetSize() const;

private:
    std::vector<std::vector<int>> m_map; // in YX format: outer vector is y coordinate or rows, inner vector is x coordinate or columns
    glm::ivec2 m_mapSize;
};