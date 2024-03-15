#pragma once
#include <SDL.h>
#include "Map.hpp"

#define PI 3.14159265359f

class Player
{
    public:
    void Update(float deltaTime, const Map &map);

    glm::vec2 m_position;

    float m_angle = PI;
    float m_fieldOfView = PI / 3.0f;
    float m_height = 0.5f;

    float m_moveSpeed = 5.0f;
    float m_strafeSpeed = 5.0f;
    float m_rotationSpeed = 5.0f;

    int m_movementDirection = 0; // 1 for up; -1 for down
    int m_strafeDirection = 0; // -1 for left; -1 for right
    int m_turnDirection = 0; // -1 for left; -1 for right
};