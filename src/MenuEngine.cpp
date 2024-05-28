#include "MenuEngine.h"

MenuEngine::MenuEngine(Window& window, boost::mutex& windowMutex, bool& mainExit) : window(window), windowMutex(windowMutex), mainExit(mainExit) {
	for (int i = 0; i < sizeof(buttons) / sizeof(MenuButton); i++) {
		setDefaultButtonStyle(buttons[i]);
		buttons[i].setPosition(window.getWidth() / 2, 200 + i*60);
	}
	buttons[0].setText("NEW GAME");
	buttons[1].setText("LOAD GAME");
	buttons[2].setText("SETTINGS");
	buttons[3].setText("EXIT");
}

void MenuEngine::setDefaultButtonStyle(MenuButton& button) {
	button.setBackgroundColor(0xAAAAAA);
	button.setBorderColor(0x444444);
	button.setBorderThickness(5);
	button.setTextSize(30);
	button.setSize(300, 50);
	button.setTextColor(0x444444);
}

void MenuEngine::setMouseOverButtonStyle(MenuButton& button) {
	button.setBackgroundColor(0xCCCCCC);
	button.setBorderColor(0x666666);
	button.setBorderThickness(4);
	button.setTextColor(0x666666);
}

void MenuEngine::start() {
	menuThread = boost::thread{ boost::bind(&MenuEngine::drawingLoop, this) };
}

void MenuEngine::stop() {
	menuThread.join();
}

void MenuEngine::drawingLoop() {
	while (!mainExit && !menuExit) {
		windowMutex.lock();
		switch (state) {
		case MenuState::MAIN:
			drawMainMenu();
			break;
		case MenuState::SETTINGS:
			break;
		}
		window.update();
		windowMutex.unlock();
	}
}

void MenuEngine::checkMouseOverButton(int x, int y) {
	for (int i = 0; i < sizeof(buttons) / sizeof(MenuButton); i++) {
		if (buttons[i].checkPointInButton(x, y)) {
			setMouseOverButtonStyle(buttons[i]);
		}
		else {
			setDefaultButtonStyle(buttons[i]);
		}
	}
}

void MenuEngine::drawMainMenu() {
	for (int i = 0; i < sizeof(buttons) / sizeof(MenuButton); i++) {
		buttons[i].draw(window);
	}
}