#include "Window.h"

Window::Window(uint32_t window_width, uint32_t window_height, uint32_t** matrix, const RectangleI& matrix_rect):
    window_(nullptr, &SDL_DestroyWindow), renderer_(nullptr, &SDL_DestroyRenderer), matrix(matrix), matrix_rect(matrix_rect)
{
    if (::SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("failed to init SDL");

    window_.reset(::SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN));
    
    if (!window_)
        throw std::runtime_error("failed to create window");

    renderer_.reset(::SDL_CreateRenderer(window_.get(), -1, 0u));
    if (!renderer_)
        throw std::runtime_error("failed to create renderer");

    
}

bool Window::events() const
{
    SDL_Event sdl_event = { 0 };
    ::SDL_PollEvent(&sdl_event);

    switch (sdl_event.type) {
    case SDL_QUIT:
        return false;
        break;
    default:
        break;
    }

    return true;
}

void Window::render(uint32_t iterations)
{
    SDL_Surface* screen = SDL_GetWindowSurface(window_.get());

    SDL_LockSurface(screen);
    uint8_t* pixel_array = (uint8_t*)screen->pixels;

    _render(matrix_rect, matrix, pixel_array, screen, iterations);

    SDL_UnlockSurface(screen);
    SDL_FreeSurface(screen);
    SDL_UpdateWindowSurface(window_.get());
}

void _render(const RectangleI& matrix_rect, uint32_t** matrix, 
    uint8_t* pixel_array, SDL_Surface* screen, uint32_t iterations) {
    
    // Which pixels we are supposed to look at
    const uint16_t start_x = matrix_rect.position.x;
    const uint16_t stop_x = matrix_rect.position.x + matrix_rect.width;

    const uint16_t start_y = matrix_rect.position.y;
    const uint16_t stop_y = matrix_rect.position.y + matrix_rect.height;

    double n;

    for (uint32_t i = 0; i < stop_x; i++)
    {
        for (uint32_t j = 0; j < stop_y; j++)
        {
            n = (double)matrix[i][j];
            if (n < iterations)
            {
                n = sqrt(n);
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 0] = cube((cos(n + 100))) * 255;    // B
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 1] = cube((cos(n + 50))) * 255;	    // G
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 2] = cube((cos(n))) * 255; 		    // R
            }
            else
            {
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 0] = 0;		// B
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 1] = 0;		// G
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 2] = 0;		// R

            }
        }
    }
}

double cube(double d1)
{
    return d1 * d1;
}