#include "Window.h"
#include <utility>

Window::Window(std::string_view title, int width, int height, bool fullscreen) : title(title), width(width), height(height), fullscreen(fullscreen) {
	if (SDL_Init(0) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return;
	}
	int rc = SDL_CreateWindowAndRenderer(title.data(), width, height, 0, &window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return;
	}
	SDL_SetWindowFullscreen(window, fullscreen);

	SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_DISABLED, SDL_SCALEMODE_LINEAR);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, title.data());

	screen = SDL_CreateRGBSurface(0, width, height, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		width, height);

	TTF_Init();

	SDL_ShowCursor();
	//SDL_HideCursor();
}

Window::~Window() {
    for (std::pair<std::string, SDL_Surface*> image : images) {
        SDL_DestroySurface(image.second);
    }
	SDL_DestroySurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

bool Window::loadImage(std::string name) {
	if (images.find(name) != images.end()) {
		return true;
	}
	std::string path = "images/" + name + ".bmp";
	SDL_Surface* image = SDL_LoadBMP(path.c_str());
	if (image == NULL) {
		return false;
	}
	images[name] = image;
	return true;
}

void Window::renderImage(std::string name, int x, int y, SDL_Rect* crop) {
	if (images.find(name) == images.end()) {
		if (!loadImage(name))
			return;
	}
	SDL_Surface* image = images[name];
	if (crop == nullptr) {
		SDL_Rect srcRect = { 0, 0, image->w, image->h };
		SDL_Rect dstRect = { x, y, image->w, image->h };
		SDL_BlitSurface(image, &srcRect, screen, &dstRect);
	}
	else {
		SDL_Rect dstRect = { x, y, crop->w, crop->h };
		SDL_BlitSurface(image, crop, screen, &dstRect);
	}
}

SDL_Surface* Window::SDL_CreateRGBSurface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
	return SDL_CreateSurface(width, height,
		SDL_GetPixelFormatEnumForMasks(depth, Rmask, Gmask, Bmask, Amask));
}

void Window::update() {
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderTexture(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Window::drawPixel(int x, int y, Uint32 color) {
	int bpp = screen->format->bytes_per_pixel;
	Uint8* p = (Uint8*)screen->pixels + (y * screen->pitch + x * bpp);
	*(Uint32*)p = color;
}

void Window::drawLine(int x, int y, int len, int dx, int dy, Uint32 color) {
	for (int i = 0; i < len; i++) {
		drawPixel(x, y, color);
		x += dx;
		y += dy;
	};
}

void Window::drawRectangle(SDL_Rect rect, Uint32 fillColor) {
	SDL_FillSurfaceRect(screen, &rect, fillColor);
}

void Window::drawCircle(int x, int y, int radius, int thickness, Uint32 fillColor) {
	for (int i = std::max(y - radius, 0); i < std::min(y + radius, height); i++) {
		for (int j = std::max(x - radius, 0); j < std::min(x + radius, width); j++) {
			int distance = ((j - x) * (j - x) + (i - y) * (i - y));
			if (distance < radius * radius && distance >(radius - thickness) * (radius - thickness))
				drawPixel(j, i, fillColor);
		}
	}
}

void Window::drawRectangle(SDL_Rect rect, int thickness, Uint32 outlineColor, Uint32 fillColor) {
	SDL_Rect borders[]{
		{ rect.x, rect.y, thickness, rect.h },
		{ rect.x, rect.y, rect.w, thickness },
		{ rect.x + rect.w - thickness, rect.y, thickness, rect.h },
		{ rect.x, rect.y + rect.h - thickness, rect.w, thickness },
	};

	SDL_FillSurfaceRect(screen, &rect, fillColor);
	for (const auto& border : borders)
		SDL_FillSurfaceRect(screen, &border, outlineColor);
}

