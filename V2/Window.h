#pragma once

#include "memory"
#include "optional"
#include "SDL.h"
#include "Rectangle.h"
#include "event_keys.h"
#include <iostream>
#include <optional>
#include "chrono"
#include <string.h>




struct SDL_Window;
struct SDL_Renderer;

using SDLWindowDelete = void (*)(SDL_Window*);
using SDLRendererDelete = void (*)(SDL_Renderer*);

/* Window is responsible for creating and destroying a window as well as rendering to it and getting events.*/
class Window
{
public:
    /* Construct a new Window. */
    Window(uint32_t window_width, uint32_t window_height, uint32_t** matrix, const RectangleI& matrix_rect);

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&&) = default;
    Window& operator=(Window&&) = default;

    uint32_t** matrix;

    RectangleI matrix_rect;

    /* Get's all events */
    std::optional<KeyEvent> events() const;

    /* Renders pixels from matrix */
    void render(uint32_t iterations);

    /* Updates the window name to show current fps */
    void show_fps() const;

private:
    /* SDL window object. */
    std::unique_ptr<SDL_Window, SDLWindowDelete> window_;

    /* SDL renderer object. Might not be needed*/
    std::unique_ptr<SDL_Renderer, SDLRendererDelete> renderer_;
};

/* Helper function for rendering and used for multi threading. */
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

/* Returns an optional Key of a keypress from the keyboard. */
std::optional<Key> map_sdl_key(SDL_Keycode sdl_code);

/* Returns a KeyEvent complete with key and mouse Coordinates. */
std::optional<KeyEvent> map_sdl_mouse(Key key);

/* Generates an average fps every 20 frames */
std::optional<double>generate_fps();