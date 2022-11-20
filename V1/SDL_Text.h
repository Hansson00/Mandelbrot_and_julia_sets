#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "string"
#include "iostream"


class SDL_Text {
public:
	SDL_Text(int font_size);
	~SDL_Text();

	void draw_text(std::string str, SDL_Surface* s, int x, int y);
private:
	TTF_Font* font;
	unsigned char font_color_r = 255;
	unsigned char font_color_g = 255;
	unsigned char font_color_b = 255;
};

