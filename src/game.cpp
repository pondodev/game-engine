#include <iostream>
#include "./constants.h"
#include "./game.h"

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 20.0f;
float projectileVelY = 30.0f;

void Game::Initialise(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "error initialising SDL" << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS);
    if (!window) {
        std::cerr << "error creating window" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "error creating renderer" << std::endl;
        return;
    }

    isRunning = true;
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

void Game::Update() {
    // wait until our next frame should be drawn
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    // calculate the delta time
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    ticksLastFrame = SDL_GetTicks();

    // clamp our delta time
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    projectilePosX += projectileVelX * deltaTime;
    projectilePosY += projectileVelY * deltaTime;
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile {
        (int) projectilePosX,
        (int) projectilePosY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}