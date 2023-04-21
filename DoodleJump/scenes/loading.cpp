#include "../scenes.h"
#include "../variables.h"

const int Global::PAD_LENGTH;
float Global::highest_pad;
float Global::offset;
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

		// background
		TexManager::add("def-bck", "themes/def/bck.png");

		// buttons
		TexManager::add("play-button", "asset/button/play-button.png");
		TexManager::add("play-button-on", "asset/button/play-button-on.png");

		// doo-doo
		TexManager::add("doo-left", "themes/def/left.png");
		TexManager::add("doo-right", "themes/def/right.png");

		// paddles
		TexManager::add("def-pad", "themes/def/tiles.png", Rect(0, 0, 118, 34));

		// sound effects
		Sound::add("jump", "audio/jump.wav");
		Sound::add("click", "audio/click.mp3");
		Sound::add("doo-shoot1", "audio/doo-shoot1.mp3");
		Sound::add("doo-shoot2", "audio/doo-shoot2.mp3");
		Sound::add("game-over", "audio/game-over.wav");

		// game songs
		Music::add("title", "audio/title.wav");
		Music::add("battle", "audio/battle.wav");

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