#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string_view>
#include <string>
#include <map>

class Window {
private:
	int width, height;
	std::string_view title;
	bool fullscreen;

	SDL_Surface* screen = nullptr;
	SDL_Texture* scrtex = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	std::map<std::string, SDL_Surface*> images;

	bool loadImage(std::string name);
	SDL_Surface* SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
public:
	Window(std::string_view title, int width, int height, bool fullscreen = false);
	~Window();
	void renderImage(std::string name, int x, int y, SDL_Rect* crop = nullptr);
	void update();
	void drawPixel(int x, int y, Uint32 color);
	void drawLine(int x, int y, int l, int dx, int dy, Uint32 color);
	void drawRectangle(SDL_Rect rect, Uint32 fillColor);
	void drawRectangle(SDL_Rect rect, int thickness, Uint32 outlineColor, Uint32 fillColor);
	void drawCircle(int x, int y, int radius, int thickness, Uint32 fillColor);
};