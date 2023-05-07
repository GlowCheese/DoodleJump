#include "Doodle.h"
#include "PadManager.h"
#include "../variables.h"
#include "Bullet.h"

Doodle::Doodle() {
	texname = "right";
	sprite = new Sprite("right");
	sprite->zoom = 0.6f; velo = Pair(0, 0);

	puca = new Sprite("puca");
	puca->zoom = 0.6f;

	njuska = new Sprite("njuska");
	njuska->zoom = 0.6f;
}

Doodle::~Doodle() {
	delete sprite;
	delete puca;
	delete njuska;
}

void Doodle::setTex(std::string tex) {
	if (texname != tex) {
		texname = tex;
		sprite->setTex(tex);
		if (tex == "left-odskok"
		|| tex == "right-odskok") {
			puca->setTex("puca-odskok");
		} else {
			puca->setTex("puca");
		}
	}
}

void Doodle::handle() {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_LEFT]) {
		setTex("left");
		velo.x -= 1 + (velo.x > 0);
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		setTex("right");
		velo.x += 1 + (velo.x < 0);
	}

	if (velo.x < 0) velo.x += std::min(-velo.x, 0.5f);
	if (velo.x > 0) velo.x += std::max(-velo.x, -0.5f);

	velo.x = std::max(-6.0f, std::min(6.0f, velo.x));

	if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
		if (Game::event.button.button == SDL_BUTTON_LEFT
		 && SDL_GetTicks() - lastShoot > 120) {
			if (Rand(0, 1)) {
				Sound::play("doo-shoot1");
			} else {
				Sound::play("doo-shoot2");
			}
			lastShoot = SDL_GetTicks();

			SDL_Point center = { sprite->pos.x_int(), sprite->pos.y_int() };
			center.x += 60 * sprite->zoom - njuska->w() / 2;

			float angle = getAngle();

			Bullet::add(center.x + sin(angle*acos(-1)/180), center.y, angle);
		}
	}
}

void Doodle::draw(int bright) {
	if (SDL_GetTicks() - lastShoot < 300) {
		puca->pos = sprite->pos;
		njuska->pos = sprite->pos;
		puca->draw(bright, Global::offset);

		SDL_Point center = { puca->pos.x_int(), puca->pos.y_int()};
		center.x += 60 * puca->zoom - njuska->w()/2;

		float angle = getAngle();
		njuska->pos = Pair(center.x, center.y);
		njuska->draw(bright, Global::offset, angle);
	} else {
		sprite->draw(bright, Global::offset);
	}
}

void Doodle::update() {
	double acc = 0.7, max_velo = -17.0;
	     if (Game::Score() <  400)  { acc = 0.40; max_velo = -13.0; }
	else if (Game::Score() <  850)  { acc = 0.45; max_velo = -13.7; }
	else if (Game::Score() < 1350)  { acc = 0.50; max_velo = -14.5; }
	else if (Game::Score() < 1900)  { acc = 0.55; max_velo = -15.2; }
	else if (Game::Score() < 2500)  { acc = 0.60; max_velo = -15.8; }
	else if (Game::Score() < 3150)  { acc = 0.65; max_velo = -16.5; }

	sprite->pos += velo; velo.y += acc;

	if (getX() + sprite->w() / 2 >= Game::Width()) {
		getX() = -sprite->w() / 2;
	}
	if (getX() + sprite->w() / 2 < 0) {
		getX() = Game::Width() - sprite->w() / 2 - 1;
	}

	if (velo.y > 0) {
		// check if doodle can jump on any paddle
		int y = getY() + sprite->h();
		int l = getX() + 22;
		int r = getX() + sprite->w() - 22;

		for (Paddle* p : PadManager::PadArray) {
			int touch = p->touch(l, r, y, velo.y);
			if (touch == 1) {
				if (p->type == CLOUD)
					Sound::play("cloud-jump");
				else
					Sound::play("jump");

				velo.y = max_velo;
				getY() = p->pos.y - sprite->h();
				lastJump = SDL_GetTicks(); break;
			} else if (touch == 2) {
				Sound::play("boing");

				velo.y = 2*max_velo;
				getY() = p->pos.y - sprite->h();
				lastJump = SDL_GetTicks(); break;
			}
		}
	}

	if (SDL_GetTicks() - lastJump <= 300) {
		if (texname == "left") setTex("left-odskok");
		if (texname == "right") setTex("right-odskok");
	} else {
		if (texname == "left-odskok") setTex("left");
		if (texname == "right-odskok") setTex("right");
	}
}

float Doodle::getAngle() {
	int x1, y1; SDL_GetMouseState(&x1, &y1);
	int x2 = getX() + sprite->w()/2, y2 = Game::Height();
	float ans = atan2(x1 - x2, y2 - y1);
	return std::max(-45.0, std::min(45.0, ans * 180 / acos(-1)));
}

float &Doodle::getX() { return sprite->pos.x; }
float &Doodle::getY() { return sprite->pos.y; }
void Doodle::setPos(float x, float y) { sprite->pos = Pair(x, y); }