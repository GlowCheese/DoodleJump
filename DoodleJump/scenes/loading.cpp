#include "scenes.h"
#include "../variables.h"

float Global::offset;
float Global::highest_pad[2];

Doodle* Global::doodle;

Sprite* MainMenu::menu;
Sprite* Jumpppp::bck;
Sprite* GameOver::bck;

Button* MainMenu::start;
Button* MainMenu::leftTheme;
Button* MainMenu::rightTheme;

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
		for (std::string s : {"play", "left", "right"}) {
			TexManager::add(s + "-button", "asset/button/" + s + "-button.png");
			TexManager::add(s + "-button-in", "asset/button/" + s + "-button-in.png");
			TexManager::add(s + "-button-on", "asset/button/" + s + "-button-on.png");
		}

		// default theme
		for (int i = 0; i < Game::theme.size(); i++) {
			Game::selectedTheme = i; std::string th = "themes/" + Game::theme[i];
			TexManager::add(Game::getThemeIMG("bck"), th + "/bck.png");
			TexManager::add(Game::getThemeIMG("left"), th + "/left.png");
			TexManager::add(Game::getThemeIMG("right"), th + "/right.png");
			TexManager::add(Game::getThemeIMG("left-odskok"), th + "/left-odskok.png");
			TexManager::add(Game::getThemeIMG("right-odskok"), th + "/right-odskok.png");
			TexManager::add(Game::getThemeIMG("pad"), th + "/tiles.png", Rect(0, 0, 118, 34));
			TexManager::add(Game::getThemeIMG("brok-0"), th + "/tiles.png", Rect(0, 143, 124, 34));
			TexManager::add(Game::getThemeIMG("brok-1"), th + "/tiles.png", Rect(0, 180, 124, 43));
			TexManager::add(Game::getThemeIMG("brok-2"), th + "/tiles.png", Rect(0, 230, 124, 58));
			TexManager::add(Game::getThemeIMG("brok-3"), th + "/tiles.png", Rect(0, 296, 124, 67));
			TexManager::add(Game::getThemeIMG("spring-0"), th + "/tiles.png", Rect(808, 198, 34, 23));
			TexManager::add(Game::getThemeIMG("spring-1"), th + "/tiles.png", Rect(808, 230, 34, 55));
			TexManager::add(Game::getThemeIMG("horz-pad"), th + "/tiles.png", Rect(0, 34, 118, 34));
			TexManager::add(Game::getThemeIMG("vert-pad"), th + "/tiles.png", Rect(0, 71, 118, 34));
		}
		Game::selectedTheme = 0;

		// sound effects
		Sound::add("boing", "audio/boing.mp3");
		Sound::add("jump", "audio/jump.wav");
		Sound::add("cloud-jump", "audio/cloud-jump.mp3");
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

		MainMenu::start = new Button("play-button");
		MainMenu::start->set_pos(90, 160);
		MainMenu::start->set_zoom(0.7f);

		Jumpppp::bck = new Sprite(Game::getThemeIMG("bck"));
		Jumpppp::bck->fill_zoom();

		GameOver::bck = new Sprite(Game::getThemeIMG("bck"));
		GameOver::bck->fill_zoom();
	}
	catch (...) {
		std::cout << "\n! An error occurred while loading textures.\n";
		throw;
	}

	std::cout << "\n* All textures loaded successfully!\n\n";

	MainMenu::init();
	Game::game_state = MAIN_MENU;
}