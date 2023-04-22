#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include <map>
#include <queue>
#include <tuple>
#include <random>
#include <chrono>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "GameSetting.h"


enum ERROR_CODE {
	BRAVO,
	INIT_ERROR,
	AUDIO_ERROR,
	TEXTURE_ERROR,
	ADDING_PADDLE
};
enum GAME_STATE {
	LOADING,
	MAIN_MENU,
	JUMPPPP,
	GAME_OVER
};


/* ========== MAIN NAMESPACE ========== */
class Game {
public:
	static GameSetting Setting;
	static GAME_STATE game_state;

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	Game() {}; ~Game() {};

	void init(), run(), quit();

	/* ========== SETTING ========== */
	static TTF_Font* Font();
	static int Width(), Height();
	static void toggleFullscreen();

	/* ========== OTHERS ========== */
	static int Score();
	static SDL_Event event;
};