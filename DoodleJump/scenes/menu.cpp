#include "scenes.h"
#include "../variables.h"

void MainMenu::init() {
	Music::play("title");
	start->state = FREE;

	Global::doodle->velo = Pair(0, 0);
	Global::doodle->setPos(35, 410);

	Global::doodle->setTex(Game::getThemeIMG("right"));

	Global::offset = 0;
	PadManager::reset();
	PadManager::add(40, 530, DEFAULT);
}
void MainMenu::handle() {
	start->handle();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	int lastTheme = Game::selectedTheme;

	if (state[SDL_SCANCODE_1]) Game::selectedTheme = 0;
	if (state[SDL_SCANCODE_2]) Game::selectedTheme = 1;
	if (state[SDL_SCANCODE_3]) Game::selectedTheme = 2;
	if (state[SDL_SCANCODE_4]) Game::selectedTheme = 3;
	if (state[SDL_SCANCODE_5]) Game::selectedTheme = 4;

	if (lastTheme != Game::selectedTheme) {
		Jumpppp::bck->setTex(Game::getThemeIMG("bck"));
		GameOver::bck->setTex(Game::getThemeIMG("bck"));
		Global::doodle->setTex(Game::getThemeIMG("right"));
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