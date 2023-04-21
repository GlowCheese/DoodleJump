#include "Doodle.h"
#include "PadManager.h"
#include "../variables.h"

Doodle::Doodle() {
	texname = "doo-right";
	sprite = new Sprite("doo-right");
	sprite->zoom = 0.7f; velo = Pair(0, 0);
}

void Doodle::setTex(const char* tex) {
	if (texname != tex) {
		texname = tex;
		sprite->setTex(tex);
	}
}

void Doodle::handle() {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT]) {
		velo.x -= 1 + (velo.x > 0);
		setTex("doo-left");
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		velo.x += 1 + (velo.x < 0);
		setTex("doo-right");
	}

	if (velo.x < 0) velo.x += std::min(-velo.x, 0.5f);
	if (velo.x > 0) velo.x += std::max(-velo.x, -0.5f);

	velo.x = std::max(-6.0f, std::min(6.0f, velo.x));
}

void Doodle::draw(int bright) {
	sprite->draw(bright, Global::offset);
}

void Doodle::update() {
	sprite->pos += velo; velo.y += 0.4f;

	if (sprite->pos.x + sprite->w() / 2 >= Game::Width()) {
		sprite->pos.x = -sprite->w() / 2;
	}
	if (sprite->pos.x + sprite->w() / 2 < 0) {
		sprite->pos.x = Game::Width() - sprite->w() / 2 - 1;
	}

	if (velo.y > 0) {
		int y = sprite->pos.y + sprite->h();
		int l = sprite->pos.x + 30;
		int r = sprite->pos.x + sprite->w() - 30;

		for (Paddle* p : PadManager::PadArray) {
			if (p->touch(l, r, y)) {
				Sound::play("jump");
				sprite->pos.y = p->pos.y - sprite->h();
				velo.y = -13; break;
			}
		}
	}
}

void Doodle::setPos(int x, int y) {
	sprite->pos = Pair(x, y);
}