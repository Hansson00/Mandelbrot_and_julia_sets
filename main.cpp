#include "iostream"
#include "Engine.h"
#include <cstdlib>
#include "string"


#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080


Engine* engine = nullptr;

int main(int argc, char* argv[]) {

	engine = new Engine(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	while (engine->running) {
		engine->events();
	}
	delete(engine);
	return 0;
}