#include "../Paddle.h"

HorzPad::HorzPad(int x, int y)
	: Paddle(x, y, DEFAULT) {
	sprite = new Sprite(Game::getThemeIMG("horz-pad"));
	sprite->zoom = 0.6f;
	width = sprite->w();
	height = sprite->h();
	padOffset = 0;

	if (Rand(1, 100) <= 10) {
		spring = new Sprite(Game::getThemeIMG("spring-0"));
		spring->zoom = 0.6f;
		spring_offset = Rand(8, 45);
	}
}

void HorzPad::update() {
	if (going_left) {
		pos.x -= 1.5f;
		padOffset -= 1.5f;
		if (padOffset < -70) {
			going_left = false;
		}
	}
	else {
		pos.x += 1.5f;
		padOffset += 1.5f;
		if (padOffset > 70) {
			going_left = true;
		}
	}
}

int HorzPad::touch(int l, int r, int y, int velo) {
	if (spring != NULL) {
		spring->pos = pos + Pair(spring_offset, -spring->h() + 5);
		if (spring->pos.y >= y && spring->pos.y <= y + velo) {
			int l2 = spring->pos.x, r2 = l2 + width - 1;
			if (r >= l2 && l <= r2) {
				spring->setTex(Game::getThemeIMG("spring-1"));
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

bool HorzPad::draw(int bright, int offset) {
	if (spring != NULL) {
		if (last_bounce != -1 && (SDL_GetTicks() - last_bounce) > 400) {
			spring->setTex(Game::getThemeIMG("spring-0"));
			last_bounce = -1;
		}
		spring->pos = pos + Pair(spring_offset, -spring->h() + 5);
		spring->draw(bright, offset);
	}

	sprite->pos = pos;
	return sprite->draw(bright, offset);
}