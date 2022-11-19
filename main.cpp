#include "iostream"
#include "Engine.h"
#include "string"

Engine* engine = nullptr;






int main(int argc, char* argv[]) {

	if (argc == 4) {
		engine = new Engine(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

		while (engine->running) {
			engine->events();
		}
		delete(engine);
	}
	else
		std::cout << "Error, invalid arguments...\n";
	return 0;
}