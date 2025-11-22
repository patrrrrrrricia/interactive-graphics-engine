#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include "glm/glm.hpp"
#include "circle.h"

//define window dimensions
constexpr int WINDOW_WIDTH{640};
constexpr int WINDOW_HEIGHT{480};

constexpr float GLOBAL_ANIMATION_SPEED{150.0f};

//define SDL Window related variables
SDL_Window *window{nullptr};
SDL_Renderer *renderer{nullptr};
SDL_Event currentEvent;
SDL_Color backgroundColor{255, 255, 255, 255};

bool quit{false};

float mouseX{-1.0f}, mouseY{-1.0f};

float displayScale{1.0f};

SDL_FRect myRectangle{100.0f, 100.0f, 200.0f, 100.0f};

Uint64 startTime, endTime, elapsedTime;

struct Rectangle {
    glm::vec2 pos;
    float width;
    float height;
    SDL_Color color;
    glm::vec2 dir;
    float speed;

    void draw(SDL_Renderer* renderer) {
        SDL_FRect tmpRect;
        tmpRect.x = pos.x - width / 2.0f;
        tmpRect.y = pos.y - height / 2.0f;
        tmpRect.w = width;
        tmpRect.h = height;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &tmpRect);
        SDL_SetRenderDrawColor(renderer, color.r / 2, color.g / 2, color.b / 2, color.a);
        SDL_RenderRect(renderer, &tmpRect);
    }
};

Rectangle r;
Circle c;

std::vector<Circle> circles;

void initRectangle() {
    r.pos = glm::vec2(150.0f, 150.0f);
    r.width = 50.0f;
    r.height = 50.0f;
    r.color = SDL_Color{255, 20, 147, 255};
    r.dir = glm::vec2(0.0f, 0.0f);
    r.speed = 1.0f;

    c.radius = 25.0f;
    c.pos = glm::vec2(250.0f, 300.0f);
    c.color = SDL_Color{230, 182, 193, 255};
    c.dir = glm::vec2(0.0f, 0.0f);
    c.speed = 0.7f;

    circles.push_back(c);
    if (circles.size() > 0) {

    }
}

bool initWindow() {
    bool success{true};

    //Try to initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s\n", SDL_GetError());
        success = false;
    } else {
        //Try to create the window and renderer
        displayScale = SDL_GetDisplayContentScale(1);

        if (!SDL_CreateWindowAndRenderer(
            "SDL Hello World Example",
            static_cast<int>(displayScale * WINDOW_WIDTH),
            static_cast<int>(displayScale * WINDOW_HEIGHT),
            0,
            &window, &renderer)) {
            SDL_Log("Failed to create window and renderer: %s\n", SDL_GetError());
            success = false;
        } else {
            //Apply global display scaling to renderer
            SDL_SetRenderScale(renderer, displayScale, displayScale);

            //Set background color
            SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                                   backgroundColor.a);

            //Apply background color
            SDL_RenderClear(renderer);
        }
    }

    return success;
}

void processEvents() {
    //Check for events in queue
    while (SDL_PollEvent(&currentEvent)) {
        //User requests quit
        if (currentEvent.type == SDL_EVENT_QUIT) {
            quit = true;
        }

        //Mouse event -> pressed button
        if (currentEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (currentEvent.button.button == SDL_BUTTON_LEFT) {
                SDL_GetMouseState(&mouseX, &mouseY);
                mouseX /= displayScale;
                mouseY /= displayScale;
                std::cout << "Left mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
            }
        }

        //Mouse event -> mouse movement
        if (currentEvent.type == SDL_EVENT_MOUSE_MOTION) {

            SDL_GetMouseState(&mouseX, &mouseY);
            mouseX /= displayScale;
            mouseY /= displayScale;

            if (const SDL_MouseButtonFlags mouseButtons = SDL_GetMouseState(nullptr, nullptr); mouseButtons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) {
                SDL_GetMouseState(&mouseX, &mouseY);
                mouseX /= displayScale;
                mouseY /= displayScale;
                std::cout << "Mouse move while left clicking => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
            }
        }

        //Keyboard event
        if (currentEvent.type == SDL_EVENT_KEY_DOWN) {
            switch (currentEvent.key.key) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_UP:
                    //std::cout << "UP arrow key was pressed" << std::endl;
                    //r.pos.y -= 5.0f;
                    break;
                case SDLK_DOWN:
                    //std::cout << "DOWN arrow key was pressed" << std::endl;
                    //r.pos.y += 5.0f;
                    break;
                case SDLK_LEFT:
                    //std::cout << "LEFT arrow key was pressed" << std::endl;
                    //r.pos.x -= 5.0f;
                    break;
                case SDLK_RIGHT:
                    //std::cout << "RIGHT arrow key was pressed" << std::endl;
                    //r.pos.x += 5.0f;
                    break;
                case SDLK_R:
                    std::cout << "R key was pressed" << std::endl;
                    break;
                case SDLK_S:
                    std::cout << "S key was pressed" << std::endl;
                    break;
                default:
                    break;
            }
        }
    }
}

void processMovement() {
    const bool* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_LEFT]) {
        r.pos.x -= 1.0f;
    }

    if (keys[SDL_SCANCODE_RIGHT]) {
        r.pos.x += 1.0f;
    }

    if (keys[SDL_SCANCODE_UP]) {
        r.pos.y -= 1.0f;
    }

    if (keys[SDL_SCANCODE_DOWN]) {
        r.pos.y += 1.0f;
    }
}

void drawFrame() {
    //Clear the background
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);

    //Draw scene
    r.draw(renderer);
    c.draw(renderer);

    //Update window
    SDL_RenderPresent(renderer);
}

void animate() {
    // Rectangle
    r.dir = glm::normalize(glm::vec2(mouseX, mouseY) - r.pos);
    r.pos += r.speed * (elapsedTime / 1000.0f) * GLOBAL_ANIMATION_SPEED * r.dir;

    // Circle
    c.dir = glm::normalize(glm::vec2(mouseX, mouseY) - c.pos);
    c.pos += c.speed * (elapsedTime / 1000.0f) * GLOBAL_ANIMATION_SPEED * c.dir;
}

void cleanup() {
    //Destroy renderer
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    //Destroy window
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    //Quit SDL
    SDL_Quit();
}

int main() {
    //Initialize window
    if (!initWindow()) {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }

    initRectangle();

    SDL_zero(currentEvent);

    //Game loop
    while (!quit) {
        startTime = SDL_GetTicks();
        processEvents();
        processMovement();
        animate();
        drawFrame();
        //for (int i = 0; i < 100000000; i++);
        endTime = SDL_GetTicks();
        elapsedTime = endTime - startTime;
    }

    cleanup();
    return 0;
}
