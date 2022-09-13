//#include "Event_Handler.h"
#include "iostream"
#include "Engine.h"


#define WIN_WIDTH 2000
#define WIN_HEIGHT 1025


Engine* engine = nullptr;



int main(int argc, char* argv[]) {
	
	engine = new Engine(WIN_WIDTH, WIN_HEIGHT);

	while (engine->running) {
		engine->events();
	}
	delete(engine);
	return 0;
}