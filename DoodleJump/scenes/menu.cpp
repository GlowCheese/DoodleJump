#include "../scenes.h"
#include "../variables.h"

void MainMenu::init() {
	Music::play("title");
	start->state = FREE;

	Global::doodle->velo = Pair(0, 0);
	Global::doodle->setPos(35, 410);

	Global::doodle->setTex("def-right");

	Global::offset = 0;
	PadManager::reset();
	PadManager::add(40, 530, DEFAULT);
}
void MainMenu::handle() {
	start->handle();
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
		}
		Jumpppp::init();
		Game::game_state = JUMPPPP;
	}
}