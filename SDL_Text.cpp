#include "SDL_Text.h"

SDL_Text::SDL_Text(int size) {

    if (TTF_Init() == -1) {
        std::cout << "Error with TTF_Init...\n";
        return;
    }
            
    font = TTF_OpenFont("./fonts/raleway/Raleway-SemiBold.ttf", size);
    if (font == nullptr) {
        std::cout << "Error with font...\n";
        return;
    }

}

SDL_Text::~SDL_Text() {
    TTF_CloseFont(font);
}

void SDL_Text::draw_text(std::string str, SDL_Window* window, int x, int y) {
    
    SDL_Surface* poggers = TTF_RenderText_Solid(font, str.c_str(), { font_color_r,font_color_g,font_color_b });
    SDL_Surface* screen = SDL_GetWindowSurface(window);
    SDL_Rect rect = {x, y, 0, 0};


    SDL_BlitSurface(poggers, NULL, screen, &rect);

    SDL_FreeSurface(screen);
    SDL_FreeSurface(poggers);
}



