#include "GameEngine.h"
#include <iostream>

void GameEngine::start() {
	menuLoop();
	mainLoop();
}

void GameEngine::menuLoop() {
	std::string test;
	while (true) {
		window.renderImage("test", 200, 200);
		window.drawCircle(100, 100, 50, 3, 0xFF0000);
		window.update();
	}
}

void GameEngine::mainLoop() {
	while (!true) {

	}
}