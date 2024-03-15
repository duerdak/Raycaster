#pragma once
#include <SDL.h>
#include <string>
#include "Player.hpp"

class Window
{
    public:
    Window();
    Window(glm::ivec2 windowSize, const std::string& title);
    ~Window();

    void ProcessInput(Player& player);

    bool IsRunning();

    void SetWindowTitle(const std::string& title);

    SDL_Window* GetWindow();
    glm::ivec2 GetWindowSize();

    private:
    void Init(glm::ivec2 windowSize = {1280, 720}, const std::string& title = "Window");

    SDL_Window *m_window;
    glm::ivec2 m_windowSize;
    bool m_isRunning;
};