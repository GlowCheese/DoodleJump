#include "../scenes.h"
#include "../variables.h"

void fixOffset() { Global::offset = std::max(Global::offset, 300 - Global::doodle->sprite->pos.y); }

void Jumpppp::init() {
	Music::play("battle");

	PadManager::reset();
	PadManager::add(40, 620, DEFAULT);

	Global::doodle->velo = Pair(0, 0);
	Global::doodle->setPos(40, 620 - Global::doodle->sprite->h());
}

void Jumpppp::handle() {
	if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
		if (Game::event.button.button == SDL_BUTTON_LEFT) {
			if (Rand(0, 1)) {
				Sound::play("doo-shoot1");
			}
			else {
				Sound::play("doo-shoot2");
			}
		}
	}
	Global::doodle->handle();
}

void Jumpppp::update() {
	Global::doodle->update();
	fixOffset();

	while (PadManager::add());
}

void Jumpppp::render() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderClear(Game::renderer);

	bck->draw();
	PadManager::draw();
	Global::doodle->draw();

	Writer::write(std::to_string(Game::Score()), Game::Width() - 10, 10, RIGHT);

	SDL_RenderPresent(Game::renderer);
}

void Jumpppp::run() {
	handle();
	update();
	render();

	if (Global::doodle->sprite->pos.y + Global::offset >= Game::Height()) {
		GameOver::init();
		Game::game_state = GAME_OVER;
	}
}