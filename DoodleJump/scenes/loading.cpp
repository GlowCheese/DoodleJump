#include "../scenes.h"
#include "../variables.h"

float Global::offset;
const int Global::PAD_NUM;
float Global::highest_pad[PAD_NUM];

Doodle* Global::doodle;
Sprite* MainMenu::menu;
Button* MainMenu::start;
Sprite* Jumpppp::bck;
Sprite* GameOver::bck;

void LoadingScene::run() {
	try {
		// rendering loading screen
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderClear(Game::renderer);

		TexManager::add("loading", "asset/loading.png");
		Sprite* loading_bg = new Sprite("loading");
		loading_bg->fill_zoom();
		loading_bg->draw();

		SDL_RenderPresent(Game::renderer);

		delete loading_bg;

		// loading textures
		TexManager::add("menu", "asset/menu.png");

		// buttons
		TexManager::add("play-button", "asset/button/play-button.png");
		TexManager::add("play-button-on", "asset/button/play-button-on.png");

		// default theme
		TexManager::add("def-bck", "themes/def/bck.png");
		TexManager::add("def-left", "themes/def/left.png");
		TexManager::add("def-right", "themes/def/right.png");
		TexManager::add("def-left-odskok", "themes/def/left-odskok.png");
		TexManager::add("def-right-odskok", "themes/def/right-odskok.png");
		TexManager::add("def-pad", "themes/def/tiles.png", Rect(0, 0, 118, 34));
		TexManager::add("def-brok-0", "themes/def/tiles.png", Rect(0, 144, 124, 33));
		TexManager::add("def-brok-1", "themes/def/tiles.png", Rect(0, 180, 124, 43));
		TexManager::add("def-brok-2", "themes/def/tiles.png", Rect(0, 230, 124, 58));
		TexManager::add("def-brok-3", "themes/def/tiles.png", Rect(0, 296, 124, 67));
		
		// sound effects
		Sound::add("jump", "audio/jump.wav");
		Sound::add("breaks", "audio/breaks.mp3");
		Sound::add("click", "audio/click.mp3");
		Sound::add("doo-shoot1", "audio/doo-shoot1.mp3");
		Sound::add("doo-shoot2", "audio/doo-shoot2.mp3");
		Sound::add("game-over", "audio/game-over.wav");

		// game songs
		Music::add("title", "audio/title.mp3");
		Music::add("battle-0", "audio/battle-0.mp3");
		Music::add("battle-1", "audio/battle-1.mp3");
		Music::add("battle-2", "audio/battle-2.mp3");
		Music::add("battle-3", "audio/battle-3.mp3");
		Music::add("battle-4", "audio/battle-4.mp3");
		Music::add("battle-5", "audio/battle-5.mp3");

		// declaring elements
		Global::doodle = new Doodle();

		MainMenu::menu = new Sprite("menu");
		MainMenu::menu->fill_zoom();

		MainMenu::start = new Button("play-button", 15);
		MainMenu::start->set_pos(90, 160);
		MainMenu::start->set_zoom(0.7f);

		Jumpppp::bck = new Sprite("def-bck");
		Jumpppp::bck->fill_zoom();

		GameOver::bck = new Sprite("def-bck");
		GameOver::bck->fill_zoom();
	}
	catch (...) {
		std::cout << "\n! An error occurred while loading textures.\n";
		throw;
	}

	std::cout << "\n* All textures loaded successfully!\n\n";
	SDL_Delay(1000);

	MainMenu::init();
	Game::game_state = MAIN_MENU;
}