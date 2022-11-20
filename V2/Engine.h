#pragma once
#include "Fractal.h"
#include "Window.h"
#include "iostream"

class Engine
{
public:
	/** Constructs an engine with a windowsize of 500x500. */
	Engine();

	/*
	* Constructs with window width and window height.
	* 
	* @param window_width
	*	Window width of the application.
	* 
	* @param window_height
	*	Window height of the application.
	*/
	Engine(uint32_t window_width, uint32_t window_height);

	/** Deconstructor. */
	//~Engine();
	
	/** Information about the fractal.*/
	Fractal* fractal;

	/** The window application. */
	Window* window;

	/** Says if the application should close or not. */
	bool running;

	/** Runs the program. */
	void main_loop();
};

