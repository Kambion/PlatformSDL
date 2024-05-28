#include "Window.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include "MenuButton.h"

enum class MenuState {
	MAIN,
	SETTINGS
};

class MenuEngine {
private:
	boost::mutex& windowMutex;
	Window& window;
	bool& mainExit;
	bool menuExit = false;
	MenuState state = MenuState::MAIN;
	boost::thread menuThread;

	MenuButton buttons[4];

	void drawingLoop();
	void drawMainMenu();
	void setDefaultButtonStyle(MenuButton& button);
	void setMouseOverButtonStyle(MenuButton& button);
public:
	MenuEngine(Window& window, boost::mutex& windowMutex, bool& mainExit);
	void start();
	void stop();
	void checkMouseOverButton(int x, int y);
};