#include "scenes.h"
#include "../variables.h"

float Global::offset;
float Global::highest_pad[2];
int Global::themeTexCount = 0;

Doodle* Global::doodle;

Sprite* MainMenu::menu;
Sprite* Jumpppp::bck;
Sprite* GameOver::bck;

Button* MainMenu::start;
Button* MainMenu::leftTheme;
Button* MainMenu::rightTheme;
Sprite* MainMenu::themeSel1;
Sprite* MainMenu::themeSel2;

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
		TexManager::add("themesel1", "asset/themesel1.png");
		TexManager::add("themesel2", "asset/themesel2.png");

		// buttons
		for (std::string s : {"play", "left", "right"}) {
			TexManager::add(s + "-button", "asset/button/" + s + "-button.png");
			TexManager::add(s + "-button-in", "asset/button/" + s + "-button-in.png");
			TexManager::add(s + "-button-on", "asset/button/" + s + "-button-on.png");
		}

		TexManager::add("def-bullet", "asset/bullets.png", Rect(1, 2, 22, 23));
		TexManager::add("ice-bullet", "asset/bullets.png", Rect(43, 64, 24, 25));
		TexManager::add("jun-bullet", "asset/bullets.png", Rect(99, 3, 27, 22));
		TexManager::add("soc-bullet", "asset/bullets.png", Rect(3, 66, 30, 40));
		TexManager::add("stn-bullet", "asset/bullets.png", Rect(99, 3, 27, 22));

		TexManager::loadTheme(0, false);

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

		MainMenu::leftTheme = new Button("left-button");
		MainMenu::leftTheme->set_pos(17, 630);
		MainMenu::leftTheme->set_zoom(0.15f);

		MainMenu::rightTheme = new Button("right-button");
		MainMenu::rightTheme->set_pos(390, 630);
		MainMenu::rightTheme->set_zoom(0.15f);

		MainMenu::themeSel1 = new Sprite("themesel1");
		MainMenu::themeSel2 = new Sprite("themesel2");
		MainMenu::themeSel1->zoom = MainMenu::themeSel2->zoom = MainMenu::menu->zoom;
		MainMenu::themeSel1->pos = {  0, Game::Height() - MainMenu::themeSel1->h()    };
		MainMenu::themeSel2->pos = { -1, Game::Height() - MainMenu::themeSel2->h()-17 };

		Jumpppp::bck = new Sprite("bck");
		Jumpppp::bck->fill_zoom();

		GameOver::bck = new Sprite("bck");
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