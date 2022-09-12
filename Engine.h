#pragma once
#include "SDL.h"
#include "Window.h"
#include "Julia.h"


class Engine {
public:
	Engine(int width, int height);
	~Engine();
	bool running;
	void events();

private:
	bool continuous_rendering = true;
	Window* screen;
	Julia* julia;
	int** pixel_matrix;
};

