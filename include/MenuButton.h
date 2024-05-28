#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.h"

enum class BackgroundStyle {
	SOLID,
	GRADIENT,
	IMAGE
};

enum class BorderStyle {
	SHARP,
	ROUNDED
};

class MenuButton {
private:
	BackgroundStyle backgroundStyle;
	BorderStyle borderStyle;
	int borderThickness;
	int cornerRadius;
	Uint32 borderColor;

	struct {
		Uint32 firstColor;
		Uint32 secondColor;
	}backgroundColor;

	std::string backgroundImage;
	SDL_Rect imageRect;
	std::string buttonText;
	Uint32 textColor;
	int textSize;
	Fonts font;

	int x, y;
	int width, height;

	void drawBackground(Window& window);
	void drawBorder(Window& window);
	void drawText(Window& window);
public:
	MenuButton();
	void draw(Window& window);
	inline void setBackgroundStyle(BackgroundStyle backgroundStyle) { this->backgroundStyle = backgroundStyle; }
	inline void setBorderStyle(BorderStyle borderStyle) { this->borderStyle = borderStyle; }
	inline void setBorderThickness(int borderThickness) { this->borderThickness = borderThickness; }
	inline void setCornerRadius(int cornerRadius) { this->cornerRadius = cornerRadius; }
	inline void setBorderColor(Uint32 color) { borderColor = color; }
	inline void setBackgroundColor(Uint32 color) { backgroundColor.firstColor = color; }
	inline void setGradientColor(Uint32 firstColor, Uint32 secondColor) { backgroundColor.firstColor = firstColor; backgroundColor.secondColor = secondColor; }
	void setBackgroundImage(std::string imageName, int startX, int startY);
	inline void setTextSize(int size) { textSize = size; }
	inline void setFont(Fonts font) { this->font = font; }
	inline void setTextColor(Uint32 color) { textColor = color; }
	inline void setPosition(int x, int y) { this->x = x; this->y = y; }
	inline void setSize(int width, int height) { this->width = width; this->height = height; }
	inline void setText(std::string text) { buttonText = text; }
	bool checkPointInButton(int x, int y);

};