#include "../Paddle.h"

CloudPad::CloudPad(int x, int y)
	: Paddle(x, y, CLOUD) {
	std::string theme = Game::theme[Game::selectedTheme];
	sprite = new Sprite("themes/" + theme + "/tiles.png", Rect(0, 107, 118, 34));
	sprite->zoom = 0.6f;
	width = sprite->w();
	height = sprite->h();
}

int CloudPad::touch(int l, int r, int y, int velo) {
	if (lastTouch != -1) return false;

	if (pos.y < y) return false;
	if (pos.y > y + velo) return false;
	int l2 = pos.x, r2 = l2 + width - 1;

	if (r < l2 || l > r2) return false;
	return lastTouch = SDL_GetTicks(), true;
}

bool CloudPad::draw(int bright, int offset) {
	if (lastTouch != -1) {
		if (SDL_GetTicks() - lastTouch > 300) {
			sprite->pos += Game::Height();
			return false;
		} else {
			SDL_SetTextureAlphaMod(sprite->tex,
				255 * (300 - (SDL_GetTicks() - lastTouch)) / 300);
		}
	}

	sprite->pos = pos;
	return sprite->draw(bright, offset);
}