#pragma once
#include "Window.h"

class GameEngine {
private:
	Window window{ "PlatformSDL", 1000, 700 };

	void menuLoop();
	void mainLoop();
public:
	void start();
};