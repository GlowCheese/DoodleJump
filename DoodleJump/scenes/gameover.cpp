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

	Writer::size = 20;
	Writer::write("Game Over!", Game::Width() / 2, pos, CENTER);

	Writer::size = 15;
	Writer::write("Your score is: " + std::to_string(Game::Score()), Game::Width() / 2, pos + 40, CENTER);

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