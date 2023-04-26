#include "Doodle.h"
#include "PadManager.h"
#include "../variables.h"

Doodle::Doodle() {
	texname = Game::getThemeIMG("right");
	sprite = new Sprite(Game::getThemeIMG("right"));
	sprite->zoom = 0.6f; velo = Pair(0, 0);
}

void Doodle::setTex(std::string tex) {
	if (texname != tex) {
		texname = tex;
		sprite->setTex(tex);
	}
}

void Doodle::handle() {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT]) {
		setTex(Game::getThemeIMG("left"));
		velo.x -= 1 + (velo.x > 0);
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		setTex(Game::getThemeIMG("right"));
		velo.x += 1 + (velo.x < 0);
	}

	if (velo.x < 0) velo.x += std::min(-velo.x, 0.5f);
	if (velo.x > 0) velo.x += std::max(-velo.x, -0.5f);

	velo.x = std::max(-6.0f, std::min(6.0f, velo.x));
}

void Doodle::draw(int bright) {
	sprite->draw(bright, Global::offset);
}

void Doodle::update() {
	double acc = 1.0, max_velo = -20.0;
	if (Game::Score() < 500)        { acc = 0.4; max_velo = -13.0; }
	else if (Game::Score() < 1000)  { acc = 0.5; max_velo = -14.5; }
	else if (Game::Score() < 1500)  { acc = 0.6; max_velo = -16.0; }
	else if (Game::Score() < 2000)  { acc = 0.8; max_velo = -19.0; }

	sprite->pos += velo; velo.y += acc;

	if (sprite->pos.x + sprite->w() / 2 >= Game::Width()) {
		sprite->pos.x = -sprite->w() / 2;
	}
	if (sprite->pos.x + sprite->w() / 2 < 0) {
		sprite->pos.x = Game::Width() - sprite->w() / 2 - 1;
	}

	if (velo.y > 0) {
		// check if doodle can jump on any paddle
		int y = sprite->pos.y + sprite->h();
		int l = sprite->pos.x + 22;
		int r = sprite->pos.x + sprite->w() - 22;

		for (Paddle* p : PadManager::PadArray) {
			int touch = p->touch(l, r, y, velo.y);
			if (touch == 1) {
				if (p->type == CLOUD)
					Sound::play("cloud-jump");
				else
					Sound::play("jump");

				velo.y = max_velo;
				sprite->pos.y = p->pos.y - sprite->h();
				lastJump = SDL_GetTicks(); break;
			} else if (touch == 2) {
				Sound::play("boing");

				velo.y = 2*max_velo;
				sprite->pos.y = p->pos.y - sprite->h();
				lastJump = SDL_GetTicks(); break;
			}
		}
	}

	if (SDL_GetTicks() - lastJump <= 300) {
		if (texname == Game::getThemeIMG("left")) setTex(Game::getThemeIMG("left-odskok"));
		if (texname == Game::getThemeIMG("right")) setTex(Game::getThemeIMG("right-odskok"));
	} else {
		if (texname == Game::getThemeIMG("left-odskok")) setTex(Game::getThemeIMG("left"));
		if (texname == Game::getThemeIMG("right-odskok")) setTex(Game::getThemeIMG("right"));
	}
}

void Doodle::setPos(int x, int y) {
	sprite->pos = Pair(x, y);
}