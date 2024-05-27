#include "Game.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp> 


void Game::start() {
	menuEngine.start();

	while (!exit) {
		boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
	}
}

