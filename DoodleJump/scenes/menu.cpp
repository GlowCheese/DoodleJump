#include "scenes.h"
#include "../variables.h"

void MainMenu::init() {
	Music::play("title");
	start->state = FREE;

	Global::doodle->velo = Pair(0, 0);
	Global::doodle->setPos(35, 410);

	Global::doodle->setTex("right");

	Global::offset = 0;
	PadManager::reset();
	PadManager::add(40, 530, DEFAULT);
}
void MainMenu::handle() {
	int lastTheme = Game::selectedTheme;

	if (Game::selectedTheme > 0) {
		leftTheme->state = FREE;
		leftTheme->handle();
		if (leftTheme->state == CLICKED) {
			TexManager::loadTheme(Game::selectedTheme-1, 1);
		}
	} else leftTheme->state = CLICKED;

	if (Game::selectedTheme+1 < Game::theme.size()) {
		rightTheme->state = FREE;
		rightTheme->handle();
		if (rightTheme->state == CLICKED) {
			TexManager::loadTheme(Game::selectedTheme+1, 1);
		}
	} else rightTheme->state = CLICKED;

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

	start->handle();
}
void MainMenu::render(int bright) {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderClear(Game::renderer);

	menu->draw(bright);
	start->draw(bright);
	PadManager::draw(bright);
	Global::doodle->draw(bright);
	
	themeSel1->pos.x = floor(-641 * themeSel1->zoom) * Game::selectedTheme;
	themeSel1->draw(bright);
	themeSel2->draw(bright);

	leftTheme->draw(bright);
	rightTheme->draw(bright);

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