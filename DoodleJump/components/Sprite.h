#pragma once
#include "Pair.h"
#include "../Game.h"
#include "../utils.h"

class Sprite {
private:
	SDL_Texture* tex;
	SDL_Rect* src;
	SDL_Rect* dest;

public:
	Pair pos;
	double zoom = 1.0f;

	int src_w() { return src->w; }
	int src_h() { return src->h; }
	int w() { return zoom * src->w; }
	int h() { return zoom * src->h; }

	void setTex(const char* title) {
		TexManager::fetch(title, tex, src);
	}

	Sprite(const char* title) {
		setTex(title);
		dest = new SDL_Rect();
	}

	~Sprite() {
		delete dest;
	}

	bool draw(int bright = 255, int offset = 0) {
		dest->w = w(); dest->x = pos.x_int();
		dest->h = h(); dest->y = pos.y_int() + offset;
		if (dest->y >= Game::Height()) return false;

		if (bright != 255) SDL_SetTextureColorMod(tex, bright, bright, bright);
		SDL_RenderCopy(Game::renderer, tex, src, dest);
		if (bright != 255) SDL_SetTextureColorMod(tex, 255, 255, 255);

		return true;
	}

	void fill_zoom() {
		zoom = 1.0f * Game::Width() / src_w();
	}
};

