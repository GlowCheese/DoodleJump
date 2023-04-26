#include "Game.h"
#include "utils.h"
#include "scenes.h"
#include "components.h"
#include "variables.h"

SDL_Event Game::event;
GameSetting Game::Setting;
GAME_STATE Game::game_state;

int Game::selectedTheme = 0;
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
std::vector<std::string> Game::theme = { "def", "ice", "jun", "soc", "stn" };

void Game::run() {
	SDL_PollEvent(&Game::event);
	switch (Game::event.type) {
	case SDL_QUIT: throw(BRAVO);
	}

	switch (game_state) {
	case LOADING: LoadingScene::run(); break;
	case MAIN_MENU: MainMenu::run(); break;
	case JUMPPPP: Jumpppp::run(); break;
	case GAME_OVER: GameOver::run(); break;
	}
}

void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		throw(INIT_ERROR);
	}

	window = SDL_CreateWindow("Doodle Jump v3.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Setting.width, Setting.height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		throw(INIT_ERROR);
	} else {
		SDL_Surface* logoSurface = IMG_Load("logo.jfif");
		SDL_SetWindowIcon(window, logoSurface);
		SDL_FreeSurface(logoSurface);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		throw(INIT_ERROR);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
		throw(INIT_ERROR);
	}

	Setting.font = TTF_OpenFont("font.ttf", 500);

	std::cout << "* This is the demo for gluchie's new game.\n";

	Music::setVolume(20);
	Sound::setVolume(60);
	game_state = LOADING;
}

void Game::quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Game::Width()  { return Setting.width;  }
int Game::Height() { return Setting.height; }
TTF_Font* Game::Font() { return Setting.font; }

int Game::Score() { return int(Global::offset / 10); }

std::string Game::getThemeIMG(std::string img) {
	return theme[selectedTheme] + "-" + img;
}
