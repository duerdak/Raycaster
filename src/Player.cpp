#include "Player.hpp"

void Player::Update(float deltaTime, const Map& map)
{
    m_angle += m_turnDirection * m_rotationSpeed * deltaTime;
    if (m_angle < 0.0f) m_angle += 2 * PI;
    if (m_angle >= 2 * PI) m_angle -= 2 * PI;

    glm::vec2 newPos = m_position;

    if (m_movementDirection != 0)
    {
        newPos.x += cosf(m_angle) * m_movementDirection * m_moveSpeed * deltaTime;
        newPos.y += sinf(m_angle) * m_movementDirection * m_moveSpeed * deltaTime;
    }

    if (m_strafeDirection != 0)
    {
        if (m_strafeDirection == -1)
        {
            newPos.x += sinf(m_angle) * m_strafeSpeed * deltaTime;
            newPos.y -= cosf(m_angle) * m_strafeSpeed * deltaTime;
        }
        else if (m_strafeDirection == 1)
        {
            newPos.x -= sinf(m_angle) * m_strafeSpeed * deltaTime;
            newPos.y += cosf(m_angle) * m_strafeSpeed * deltaTime;
        }
    }

    // Check for wall collision before updating player position
    if (newPos.x >= 0 && newPos.x < map.GetSize().x &&
        newPos.y >= 0 && newPos.y < map.GetSize().y &&
        map.GetMap()[static_cast<int>(newPos.y)][static_cast<int>(newPos.x)] == 0)
    {
        m_position = newPos;
    }
}