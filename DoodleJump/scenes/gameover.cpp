#include "scenes.h"
#include "../variables.h"

void GameOver::init() {
	Music::stop();
	Sound::play("game-over");
	PadManager::reset();
}

void GameOver::handle() {

}

void GameOver::render(int pos, int bright = 255) {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderClear(Game::renderer);

	bck->draw(bright);
	Writer::write("Game Over!", Game::Width() / 2, pos, CENTER);

	SDL_RenderPresent(Game::renderer);
}

void GameOver::run() {
	handle();

	for (int i = Game::Height(); i >= Game::Height() / 2 - 100; i -= 2) {
		render(i, std::min(255, i - (Game::Height() / 2 - 100)));
		SDL_PollEvent(&Game::event);
		switch (Game::event.type) {
		case SDL_QUIT: throw(BRAVO);
		}
	}

	MainMenu::init();
	Game::game_state = MAIN_MENU;
}