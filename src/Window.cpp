#include "Window.hpp"
#include <SDL_image.h>

Window::Window()
{
    Init();
}

Window::Window(glm::ivec2 windowSize, const std::string& title)
{
    Init(windowSize, title);
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    SDL_Quit();
}

void Window::ProcessInput(Player& player)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                m_isRunning = false;
                break;
            }
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    m_isRunning = false;
                }
                if (event.key.keysym.sym == SDLK_w)
                {
                    player.m_movementDirection = 1;
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    player.m_movementDirection = -1;
                }
                if (event.key.keysym.sym == SDLK_a)
                {
                    player.m_strafeDirection = -1;
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    player.m_strafeDirection = 1;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    player.m_turnDirection = -1;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    player.m_turnDirection = 1;
                }
                if (event.key.keysym.sym == SDLK_r)
                {
                    player.m_angle = 90.0f;
                    player.m_position = { 2.0f, 2.0f };
                }
                break;
            }
            case SDL_KEYUP:
            {
                if (event.key.keysym.sym == SDLK_w)
                {
                    player.m_movementDirection = 0;
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    player.m_movementDirection = 0;
                }
                if (event.key.keysym.sym == SDLK_a)
                {
                    player.m_strafeDirection = 0;
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    player.m_strafeDirection = 0;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    player.m_turnDirection = 0;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    player.m_turnDirection = 0;
                }
                break;
            }
        }
    }
}

bool Window::IsRunning()
{
    return m_isRunning;
}

void Window::SetWindowTitle(const std::string& title)
{
    SDL_SetWindowTitle(m_window, title.c_str());
}

SDL_Window* Window::GetWindow()
{
    return m_window;
}

glm::ivec2 Window::GetWindowSize()
{
    return m_windowSize;
}

void Window::Init(glm::ivec2 windowSize, const std::string& title)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Failed to initialize SDL. SDL_Error: %s\n", SDL_GetError());
    }

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, 0);
    if (!m_window)
    {
        printf("Failed to create window. SDL_Error: %s\n", SDL_GetError());
    }

    // Initialize SDL_image for loading in textures
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("Failed to initialize SDL_image. IMG_Error: %s\n", IMG_GetError());
    }

    m_windowSize = windowSize;
    m_isRunning = true;
}
