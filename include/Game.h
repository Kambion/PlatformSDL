#pragma once
#include "Window.h"
#include "MenuEngine.h"

class Game {
private:
	boost::mutex windowMutex;
	bool exit = false;
	Window window{ "PlatformSDL", 1000, 700, false };
	MenuEngine menuEngine{ window, windowMutex, exit };
public:
	void start();
};