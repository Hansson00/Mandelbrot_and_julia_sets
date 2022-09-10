#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "string"
#include "iostream"


class SDL_Text {
private:
	TTF_Font* font;
	unsigned char font_color_r = 255;
	unsigned char font_color_g = 255;
	unsigned char font_color_b = 255;
public:
	SDL_Text(int font_size);
	void draw_text(std::string str, SDL_Window* renderer, int x, int y, int width, int height);
	void clean_up();
};

