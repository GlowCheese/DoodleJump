#include "scenes.h"
#include "../variables.h"

float newOffset;
void fixOffset() {
	newOffset = std::max({ newOffset, Global::offset, 300 - Global::doodle->sprite->pos.y });
	Global::offset += (newOffset - Global::offset) * 0.05f;
	
	if (Game::Score() >= 3000) Global::offset += 0.5f;
}

void Jumpppp::init() {
	std::string tmp = "battle-";
	tmp += '0' + Rand(0, 5);
	Music::play(tmp.c_str());
	
	newOffset = -Game::Height();

	PadManager::reset();
	PadManager::add(40, 600, DEFAULT);

	Global::doodle->velo = Pair(0, 0);
	Global::doodle->setPos(40, 600 - Global::doodle->sprite->h());
}

void Jumpppp::handle() {
	Global::doodle->handle();
}

void Jumpppp::update() {
	Global::doodle->update();
	fixOffset();

	while (PadManager::add());
	PadManager::update();

	Bullet::update();
}

void Jumpppp::render() {
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderClear(Game::renderer);

	bck->draw();
	PadManager::draw();
	Global::doodle->draw();
	Bullet::draw();

	Writer::size = 15;
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