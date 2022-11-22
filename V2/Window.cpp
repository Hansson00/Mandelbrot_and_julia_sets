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


std::optional<Key> map_sdl_key(SDL_Keycode sdl_code)
{
    using enum Key;

    switch (sdl_code)
    {
    case SDLK_ESCAPE: return ESC;
    case SDLK_w: return W;
    case SDLK_a: return A;
    case SDLK_s: return S;
    case SDLK_d: return D;
    case SDLK_1: return ONE;
    case SDLK_2: return TWO;
    case SDLK_3: return THREE;
    case SDLK_LSHIFT: return LSHIFT;
    case SDLK_LCTRL: return LCTRL;
    case SDLK_PAGEUP: return PGUP;
    case SDLK_PAGEDOWN: return PGDN;
    default: return std::nullopt;
    }
}


std::optional<KeyEvent> map_sdl_mouse(Key key)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    return KeyEvent{ .key_state = KeyState::DOWN,
    .key = key, .mouse_x = (uint32_t) mouse_x, .mouse_y = (uint32_t)mouse_y };
}


std::optional<KeyEvent> Window::events() const
{
    SDL_Event sdl_event = { 0 };
    SDL_PollEvent(&sdl_event);

    std::optional<KeyEvent> key_event{};

    switch (sdl_event.type) {

    case SDL_KEYDOWN:
        if (const auto key = map_sdl_key(sdl_event.key.keysym.sym); key)
        {
            if (key == Key::LSHIFT || key == Key::LCTRL)
            {
                return map_sdl_mouse(key.value());
            }
            else
            {
                return KeyEvent{ .key_state = KeyState::DOWN,.key = *key };
            }
        } 
        break;
    case SDL_MOUSEBUTTONDOWN:
        return map_sdl_mouse(Key::LMOUSE);
    case SDL_QUIT:
        return KeyEvent{ .key_state = KeyState::DOWN,.key = Key::ESC };
    default:
        break;
    }

    return key_event;
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

    show_fps();
}

void _render(const RectangleI& matrix_rect, uint32_t** matrix, 
    uint8_t* pixel_array, SDL_Surface* screen, uint32_t iterations) {
    
    static const double cos50 = cos(50 * 2) * 255 * 0.5;
    static const double cos100 = cos(100 * 2) * 255 * 0.5;
    static const double sin50 = sin(50 * 2) * 255 * 0.5;
    static const double sin100 = sin(100 * 2) * 255 * 0.5;

    // Which pixels we are supposed to look at
    const uint16_t start_x = matrix_rect.position.x;
    const uint16_t stop_x = matrix_rect.position.x + matrix_rect.width;

    const uint16_t start_y = matrix_rect.position.y;
    const uint16_t stop_y = matrix_rect.position.y + matrix_rect.height;

    // Iterations variable
    double n;

    for (uint32_t i = 0; i < stop_x; i++)
    {
        for (uint32_t j = 0; j < stop_y; j++)
        {
            n = (double)matrix[i][j];
            // If infinity color pixels
            if (n < iterations)
            {
                // Color algorithm
                n = sqrt(n);

                //const double c1 = cube(cos(n + 100)) * 255;
                //const double c2 = cube(cos(n + 50)) * 255;
                //const double c3 = cube(cos(n)) * 255;

                //const double c1 = (cos((n + 100) * 2) +1) * 255 * 0.5;
                //const double c2 = (cos((n + 50) * 2) +1) * 255 * 0.5;
                //const double c3 = (cos((n) * 2) +1) * 255 * 0.5;

                const double cosn = cos(n * 2);
                const double sinn = sin(n * 2);
                
                const double c1 = (cosn * cos100 - sinn * sin100) + 1 * 255 * 0.5;
                const double c2 = (cosn * cos50  - sinn * sin50)  + 1 * 255 * 0.5;
                const double c3 = cosn * 255 * 0.5 + 1 * 255 * 0.5;

          
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 0] = c1;    // B
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 1] = c2;    // G
                pixel_array[j * screen->pitch + i * screen->format->BytesPerPixel + 2] = c3;    // R
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

void Window::show_fps() const {

    if (const auto fps = generate_fps(); fps) {
        std::string str = "Mandelbrot " + std::to_string(1 / fps.value());
        SDL_SetWindowTitle(window_.get(), str.c_str());
    }
}

std::optional<double>generate_fps()
{
    static auto start = std::chrono::system_clock::now();
    static double average_fps = 0;
    static uint8_t count = 0;
    
    std::optional<double> fps;

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    average_fps += diff.count();

    if (count > 20)
    {
        fps = average_fps / 20;
        count = 0;
        average_fps = 0;
    }

    count++;
    start = std::chrono::system_clock::now();
    return fps;
}


double cube(double d1)
{
    return d1 * d1;
}
