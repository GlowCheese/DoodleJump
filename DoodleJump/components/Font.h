#pragma once
#include <string>
#include "SDL_ttf.h"

class Font {
public:
	std::string ttf = "asset/DMMono.ttf";
	int size = 30; SDL_Color color = { 0, 0, 0 };
};