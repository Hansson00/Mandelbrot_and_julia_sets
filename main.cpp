
#include "Window.h"

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000


Window* window = nullptr;


int main(int argc, char* argv[]) {

	window = new Window(WIN_WIDTH, WIN_HEIGHT);

	while (window->running) {
		window->draw();
	}
	window->clean_up();

	return 0;
}