#include "Window.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

class MenuEngine {
private:
	boost::mutex& windowMutex;
	Window& window;
	bool& exit;
	void mainLoop();
public:
	MenuEngine(Window& window, boost::mutex& windowMutex, bool& exit);
	void start();
};