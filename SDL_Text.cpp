#include "SDL_Text.h"

SDL_Text::SDL_Text(int size) {

    if (TTF_Init() == -1) {
        std::cout << "Error with TTF_Init...\n";
        return;
    }
            
    font = TTF_OpenFont("./fonts/raleway/Raleway-Regular.ttf", size);
    if (font == nullptr) {
        std::cout << "Error with font...\n";
        return;
    }

}

void SDL_Text::draw_text(std::string str, SDL_Window* window, int x, int y, int width, int height) {
    
    SDL_Surface* poggers = TTF_RenderText_Solid(font, str.c_str(), { font_color_r,font_color_g,font_color_b });
    SDL_Surface* screen = SDL_GetWindowSurface(window);
    
    SDL_BlitSurface(poggers, NULL, screen, NULL);

    SDL_FreeSurface(screen);
    SDL_FreeSurface(poggers);
}

void SDL_Text::clean_up() {
	TTF_CloseFont(font);
}


