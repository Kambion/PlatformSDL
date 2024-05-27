#include "SDL3/SDL_main.h"
#include "Game.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	Game game;
	game.start();
	return 0;
};