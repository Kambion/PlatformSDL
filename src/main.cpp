#include "SDL3/SDL_main.h"
#include "GameEngine.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	GameEngine gameEngine;
	gameEngine.start();
	return 0;
};