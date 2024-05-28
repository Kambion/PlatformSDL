#include "MenuButton.h"

MenuButton::MenuButton() {
	backgroundStyle = BackgroundStyle::SOLID;
	borderStyle = BorderStyle::SHARP;
	borderThickness = 0;
	cornerRadius = 0;
	borderColor = 0x000000;
	backgroundColor.firstColor = 0xFFFFFF;
	backgroundColor.secondColor = 0x000000;
	backgroundImage = "null";
	imageRect = { 0,0, width, height };
	buttonText = "test";
	textSize = 10;
	textColor = 0x000000;
	font = Fonts::RUSSO_ONE;
	x = 500;
	y = 350;
	width = 100;
	height = 30;
}

void MenuButton::draw(Window& window) {
	drawBackground(window);
	drawBorder(window);
	drawText(window);
}

void MenuButton::drawBackground(Window& window) {
	switch (backgroundStyle)
	{
	case BackgroundStyle::SOLID:
		window.drawRectangle({ x - width / 2, y - height / 2, width, height }, backgroundColor.firstColor);
		break;
	case BackgroundStyle::GRADIENT:
		//TBD
		break;
	case BackgroundStyle::IMAGE:
		window.renderImage(backgroundImage, x - width / 2, y - height / 2, &imageRect);
		break;
	}
}

void MenuButton::drawBorder(Window& window) {
	if (borderThickness > 0) {
		switch (borderStyle)
		{
		case BorderStyle::SHARP:
			window.drawRectangle({ x - width / 2, y - height / 2, borderThickness, height }, borderColor); //left
			window.drawRectangle({ x - width / 2, y - height / 2, width, borderThickness }, borderColor); //top
			window.drawRectangle({ x + width / 2 - borderThickness, y - height / 2, borderThickness, height }, borderColor); //right
			window.drawRectangle({ x - width / 2, y + height / 2 - borderThickness, width, borderThickness }, borderColor); //bottom
				break;
		case BorderStyle::ROUNDED:
			//TBD
			break;
		}
	}
}

void MenuButton::drawText(Window& window) {
	window.drawString({ x - width / 2, y - height / 2, width, height }, buttonText, textSize, font, textColor);
}

void MenuButton::setBackgroundImage(std::string imageName, int startX, int startY) {
	backgroundImage = imageName;
	imageRect = { startX, startY, width, height };
}

bool MenuButton::checkPointInButton(int x, int y) {
	SDL_Point point = { x, y };
	SDL_Rect rect = { this->x - width / 2, this->y - height / 2, width, height };


	return SDL_PointInRect(&point, &rect);
}