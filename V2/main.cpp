#include "iostream"
#include "string"
#include "Engine.h"


Engine* engine;

int main(int argc, char* argv[]) {

	engine = new Engine(500, 500);
	engine->main_loop();
	return 0;
}