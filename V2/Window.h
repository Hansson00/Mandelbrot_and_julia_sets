#pragma once

#include "memory"
#include "optional"
#include "SDL.h"
#include "iostream"
#include "Rectangle.h"

struct SDL_Window;
struct SDL_Renderer;

using SDLWindowDelete = void (*)(SDL_Window*);
using SDLRendererDelete = void (*)(SDL_Renderer*);



/** Window is responsible for creating and destroying a window as well as rendering to it and getting events.*/
class Window
{
public:
    /** Construct a new Window. */
    Window(uint32_t window_width, uint32_t window_height, uint32_t** matrix, const RectangleI& matrix_rect);

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&) = default;
    Window& operator=(Window&&) = default;

    uint32_t** matrix;

    RectangleI matrix_rect;

    /** Get's all events */
    bool events() const;

    /** Renders pixels from matrix */
    void render(uint32_t iterations);

private:
    /** SDL window object. */
    std::unique_ptr<SDL_Window, SDLWindowDelete> window_;

    /** SDL renderer object. */
    std::unique_ptr<SDL_Renderer, SDLRendererDelete> renderer_;
};

/*
* Helper function for rendering and used for multi threading.
*/
void _render(const RectangleI& matrix_rect, uint32_t** matrix, 
    uint8_t* pixel_array, SDL_Surface* screen, uint32_t iterations);

/*
* Cubes incoming double
* 
* @param d1
*   number to cube.
* 
* @returns
*   d1 * d1.
*/
double cube(double d1);