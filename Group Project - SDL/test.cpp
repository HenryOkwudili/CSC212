#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

// Constants for window size
const int SCREEN_WIDTH = 1000;
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

    SDL_Texture* backgroundTexture = loadTexture("./Assets/brick11.jpg");
    SDL_Texture* frameTexture = loadTexture("./Assets/Frame.png");
    SDL_Texture* textureLeft = loadTexture("./Assets/blender.jpg");
    SDL_Texture* textureRight = loadTexture("./Assets/openglcube.png");

    if (backgroundTexture == NULL || frameTexture == NULL || textureLeft == NULL || textureRight == NULL) {
        printf("Failed to load one or more textures!\n");
        closeSDL();
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);

        // Render the background
        SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);

        // Calculate positions to center the frames and images
        int frameWidth = 350;
        int frameHeight = 250;
        int imageWidth = 300;
        int imageHeight = 200;
        int totalFramesWidth = 2 * frameWidth + 150; // Width of both frames plus the gap
        int startX = (SCREEN_WIDTH - totalFramesWidth) / 2; // Starting x-coordinate to center both frames

        // Define position and size for the left frame and image
        SDL_Rect leftFrameDest = { startX, (SCREEN_HEIGHT - frameHeight) / 2, frameWidth, frameHeight };
        SDL_RenderCopy(gRenderer, frameTexture, NULL, &leftFrameDest);

        SDL_Rect leftImageDest = { leftFrameDest.x + (frameWidth - imageWidth) / 2, leftFrameDest.y + (frameHeight - imageHeight) / 2, imageWidth, imageHeight };
        SDL_RenderCopy(gRenderer, textureLeft, NULL, &leftImageDest);

        // Define position and size for the right frame and image
        SDL_Rect rightFrameDest = { leftFrameDest.x + frameWidth + 150, (SCREEN_HEIGHT - frameHeight) / 2, frameWidth, frameHeight };
        SDL_RenderCopy(gRenderer, frameTexture, NULL, &rightFrameDest);

        SDL_Rect rightImageDest = { rightFrameDest.x + (frameWidth - imageWidth) / 2, rightFrameDest.y + (frameHeight - imageHeight) / 2, imageWidth, imageHeight };
        SDL_RenderCopy(gRenderer, textureRight, NULL, &rightImageDest);

        SDL_RenderPresent(gRenderer);
    }

    // Free resources and close SDL
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(frameTexture);
    SDL_DestroyTexture(textureLeft);
    SDL_DestroyTexture(textureRight);
    closeSDL();

    return 0;
}
