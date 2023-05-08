	#pragma once
#include "SDL.h"

class GameSetting {
public:
	int soundvolume = 0;
	int musicvolume = 0;
	int width  = 450;
	int height = 675;
	TTF_Font* font;
};