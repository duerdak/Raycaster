#pragma once
#include <string>
#include "Window.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

class Game
{
public:
    Game();
    ~Game();

    void ProcessInput();
    void Update(float deltaTime);
    void Render();

    void Run();

private:
    glm::ivec2 m_windowSize;

    Window m_window;
    Renderer m_renderer;
    Map m_map;
    Player m_player;
};