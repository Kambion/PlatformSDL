#include "Window.h"

class GameEngine {
private:
	Window window{ "PlatformSDL", 1000, 700 };

	void mainLoop();
public:
	void start();
};