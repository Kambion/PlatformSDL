#include "MenuEngine.h"

MenuEngine::MenuEngine(Window& window, boost::mutex& windowMutex, bool& exit) : window(window), windowMutex(windowMutex), exit(exit) {

}

void MenuEngine::start() {
	boost::thread menuThread{ boost::bind(&MenuEngine::mainLoop, this) };
}

void MenuEngine::mainLoop() {
	int x = 100;
	while (!exit) {
		windowMutex.lock();

		window.clearWindow();
		window.drawCircle(x, 350, 100, 5, 0xFF00000);
		window.update();

		x = (x + 1) % 1000;

		windowMutex.unlock();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
	}
}