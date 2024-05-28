#include "Game.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp> 
#include <iostream>


void Game::start() {
	menuEngine.start();

	while (!exit) {
		events();
	}
}

void Game::events() {
	SDL_Event event;
	float x, y;
	SDL_GetMouseState(&x, &y);
	menuEngine.checkMouseOverButton(x, y);
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				//exit_button_pressed();
				exit = true;
				menuEngine.stop();
				break;
			}
			break;
		case SDL_EVENT_QUIT:
			//exit program action
			break;
		};
	};
}

