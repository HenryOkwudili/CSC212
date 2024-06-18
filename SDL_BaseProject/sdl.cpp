#include "test.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <stdlib.h>  // For random numbers
#include <time.h>    // For seeding random number generator

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 72;

struct Ball {
    int x, y;
    int dx, dy;
};

Ball ball;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("2D Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

void updateBall() {
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Boundary checks
    if (ball.x < 0) {
        ball.x = 0; // Keep within left boundary
        ball.dx *= -1;
    }
    else if (ball.x + BALL_RADIUS > SCREEN_WIDTH) {
        ball.x = SCREEN_WIDTH - BALL_RADIUS; // Keep within right boundary
        ball.dx *= -1;
    }

    if (ball.y < 0) {
        ball.y = 0; // Keep within top boundary
        ball.dy *= -1;
    }
    else if (ball.y + BALL_RADIUS > SCREEN_HEIGHT) {
        ball.y = SCREEN_HEIGHT - BALL_RADIUS; // Keep within bottom boundary
        ball.dy *= -1;
    }
}

void randomizeDirection() {
    ball.dx = (rand() % 11) - 5; // Random dx between -5 and 5
    ball.dy = (rand() % 11) - 5; // Random dy between -5 and 5
}

int main(int argc, char* argv[]) {
    srand(time(NULL));  // Seed random number generator
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    SDL_Texture* ballText = loadTexture("./Assets/ball.png");
    randomizeDirection(); // Random initial direction
    ball.x = SCREEN_WIDTH / 2 - BALL_RADIUS / 2;
    ball.y = SCREEN_HEIGHT / 2 - BALL_RADIUS / 2;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);
        updateBall();
        SDL_Rect ballRect = { ball.x, ball.y, BALL_RADIUS, BALL_RADIUS };
        SDL_RenderCopy(gRenderer, ballText, NULL, &ballRect);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(10);  // Delay to control frame rate
    }

    SDL_DestroyTexture(ballText);
    closeSDL();
    return 0;
}

On Mon, May 6, 2024 at 4:37 PM 5STAR MYZE <ayomidemalik11@gmail.com> wrote :
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

    // Constants for window size
    const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// SDL variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Load a texture from a file
SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// Initialize SDL components
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("2D Rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

// Clean up and close SDL
void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    SDL_Texture* textureTop = loadTexture("./Assets/ball.png");
    SDL_Texture* textureBottom = loadTexture("./Assets/grassfloor.png");

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);

        // Define position and size for the top image
        SDL_Rect topDest = { (SCREEN_WIDTH - 400) / 2, 30, 400, 200 }; // Centered and leaving space
        SDL_RenderCopy(gRenderer, textureTop, NULL, &topDest);

        // Define position and size for the bottom image
        SDL_Rect bottomDest = { (SCREEN_WIDTH - 400) / 2, SCREEN_HEIGHT - 230, 400, 200 }; // Centered and leaving space
        SDL_RenderCopy(gRenderer, textureBottom, NULL, &bottomDest);

        SDL_RenderPresent(gRenderer);
    }

    // Free resources and close SDL
    SDL_DestroyTexture(textureTop);
    SDL_DestroyTexture(textureBottom);
    closeSDL();

    return 0;
}