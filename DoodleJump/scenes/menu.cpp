#include "scenes.h"
#include "../variables.h"

void MainMenu::init() {
	Music::play("title");
	start->state = FREE;
	leftTheme->state = FREE;

	Global::doodle->velo = Pair(0, 0);
	Global::doodle->setPos(35, 410);

	Global::doodle->setTex("right");

	Global::offset = 0;
	PadManager::reset();
	PadManager::add(40, 530, DEFAULT);
}
void MainMenu::handle() {
	start->handle();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	int lastTheme = Game::selectedTheme;

	if (Game::event.type == SDL_KEYUP) {
		switch (Game::event.key.keysym.sym) {
		case SDLK_1: TexManager::loadTheme(0, 1); break;
		case SDLK_2: TexManager::loadTheme(1, 1); break;
		case SDLK_3: TexManager::loadTheme(2, 1); break;
		case SDLK_4: TexManager::loadTheme(3, 1); break;
		case SDLK_5: TexManager::loadTheme(4, 1); break;
		}
	}

	if (lastTheme != Game::selectedTheme) {
		Jumpppp::bck->setTex("bck");
		GameOver::bck->setTex("bck");

		Pair old_velo = Global::doodle->velo;
		float old_x = Global::doodle->getX();
		float old_y = Global::doodle->getY();

		delete Global::doodle;
		Global::doodle = new Doodle();
		Global::doodle->velo = old_velo;
		Global::doodle->setPos(old_x, old_y);

		PadManager::reset();
		PadManager::add(40, 530, DEFAULT);
	}
}
void MainMenu::render(int bright) {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderClear(Game::renderer);

	menu->draw(bright);
	start->draw(bright);
	PadManager::draw(bright);
	Global::doodle->draw(bright);

	SDL_RenderPresent(Game::renderer);
}
void MainMenu::update() {
	Global::doodle->update();
}
void MainMenu::run() {
	handle();
	update();
	render();
	if (start->state == CLICKED) {
		for (int bright = 255; bright >= 0; bright -= 5) {
			update();
			render(bright);
			SDL_PollEvent(&Game::event);
			switch (Game::event.type) {
			case SDL_QUIT: throw(BRAVO);
			}
		}
		Jumpppp::init();
		Game::game_state = JUMPPPP;
	}
}