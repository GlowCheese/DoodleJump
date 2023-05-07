#include "../Paddle.h"

BrokenPad::~BrokenPad() {
	delete sprite[0];
	delete sprite[1];
	delete sprite[2];
	delete sprite[3];
}

SDL_Rect BrokenPad::getRect() {
	int x = pos.x - 3;
	int y = pos.y - 3;
	int w = sprite[0]->w() + 3;
	int h = sprite[0]->h() + 3;

	return { x, y, w, h };
}

BrokenPad::BrokenPad(int x, int y) : Paddle(x, y, BROKEN) {
	sprite[0] = new Sprite("brok-0");
	sprite[1] = new Sprite("brok-1");
	sprite[2] = new Sprite("brok-2");
	sprite[3] = new Sprite("brok-3");
	for (int i = 0; i < 4; sprite[i++]->zoom = 0.55f);
	width = sprite[0]->w();
	height = sprite[0]->h();
}

int BrokenPad::touch(int l, int r, int y, int velo) {
	if (lastTouch != -1) return false;

	if (pos.y < y) return false;
	if (pos.y > y + velo) return false;
	int l2 = pos.x, r2 = l2 + width - 1;
	if (r >= l2 && l <= r2) {
		lastTouch = SDL_GetTicks();
		Sound::play("breaks");
	}

	return false;
}

bool BrokenPad::draw(int bright, int offset) {
	if (lastTouch == -1) {
		sprite[0]->pos = pos;
		return sprite[0]->draw(bright, offset);
	}
	else {
		unsigned int k = std::min(3u, (SDL_GetTicks() - lastTouch) / 100 + 1);

		pos.y += 4;
		sprite[k]->pos = pos;
		return sprite[k]->draw(bright, offset);
	}
}