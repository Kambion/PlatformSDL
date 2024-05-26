#include "Window.h"


Window::Window(std::string_view title, int width, int height, bool fullscreen) : title(title), width(width), height(height), fullscreen(fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.data(), width, height, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}