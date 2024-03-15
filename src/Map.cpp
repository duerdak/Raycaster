#include "Map.hpp"

Map::Map(std::vector<std::vector<int>> map): m_map(map), m_mapSize(static_cast<int>(m_map[0].size()), static_cast<int>(m_map.size()))
{
}

const std::vector<std::vector<int>> &Map::GetMap() const
{
    return m_map;
}
glm::ivec2 Map::GetSize() const
{
    return m_mapSize;
}