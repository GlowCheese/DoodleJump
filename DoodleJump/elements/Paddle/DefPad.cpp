#include "../Paddle.h"

DefPad::DefPad(int x, int y)
	: Paddle(x, y, DEFAULT) {
	sprite = new Sprite("def-pad");
	sprite->zoom = 0.6f;
	width = sprite->w();
	height = sprite->h();
}

bool DefPad::touch(int l, int r, int y, int velo) {
	if (sprite->pos.y < y) return false;
	if (sprite->pos.y > y + velo) return false;
	int l2 = sprite->pos.x, r2 = l2 + width - 1;
	return r >= l2 && l <= r2;
}

bool DefPad::draw(int bright, int offset) {
	sprite->pos = pos;
	return sprite->draw(bright, offset);
}