#include "../Paddle.h"

DefPad::DefPad(int x, int y)
	: Paddle(x, y, DEFAULT) {
	sprite = new Sprite("pad");
	sprite->zoom = 0.6f;
	width = sprite->w();
	height = sprite->h();

	if (Rand(1, 100) <= 10) {
		spring = new Sprite("spring-0");
		spring->zoom = 0.6f;
		spring_offset = Rand(8, 45);
	} else {
		spring = NULL;
		spring_offset = 0;
	}
}

int DefPad::touch(int l, int r, int y, int velo) {
	if (spring != NULL) {
		spring->pos = pos + Pair(spring_offset, -spring->h() + 5);
		if (spring->pos.y >= y && spring->pos.y <= y + velo) {
			int l2 = spring->pos.x, r2 = l2 + width - 1;
			if (r >= l2 && l <= r2) {
				spring->setTex("spring-1");
				last_bounce = SDL_GetTicks();
				return 2;
			}
		}
	}

	if (pos.y < y) return false;
	if (pos.y > y + velo) return false;
	int l2 = pos.x, r2 = l2 + width - 1;
	return r >= l2 && l <= r2;
}

bool DefPad::draw(int bright, int offset) {
	if (spring != NULL) {
		if (last_bounce != -1 && (SDL_GetTicks() - last_bounce) > 400) {
			spring->setTex("spring-0");
			last_bounce = -1;
		}
		spring->pos = pos + Pair(spring_offset, -spring->h() + 5);
		spring->draw(bright, offset);
	}

	sprite->pos = pos;
	return sprite->draw(bright, offset);
}