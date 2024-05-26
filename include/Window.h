#include <SDL3/SDL.h>
#include <string_view>

class Window {
private:
	SDL_Window* window;
	int width;
	int height;
	std::string_view title;
	bool fullscreen;
public:
	Window(std::string_view title, int width, int height, bool fullscreen = false);
	~Window();
};