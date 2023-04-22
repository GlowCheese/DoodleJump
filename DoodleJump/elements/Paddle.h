#pragma once
#include "../Game.h"
#include "../utils.h"
#include "../components.h"

enum PadType { DEFAULT = 0, BROKEN = 1 };

class Paddle {
public:
	Pair pos; PadType type;
	int width = 0, height = 0;

	~Paddle() {}
	Paddle(int x, int y, PadType type) : pos(x, y), type(type) {}
	
	virtual bool touch(Paddle* another) {
		int x1 = pos.x, y1 = pos.y;
		int w1 = width, h1 = height;

		int x2 = another->pos.x, y2 = another->pos.y;
		int w2 = another->width, h2 = another->height;

		return x1 <= x2 + w2 && x1 + w1 >= x2 && y1 <= y2 + h2 && y1 + h1 >= y2;
	}
	virtual bool touch(int l, int r, int y) { return false; }
	virtual bool draw(int bright = 255, int offset = 0) { return false; }
};

class DefPad : public Paddle {
public:
	Sprite* sprite;
	DefPad(int x, int y)
		: Paddle(x, y, DEFAULT) {
		sprite = new Sprite("def-pad");
		sprite->zoom = 0.6f;
		width = sprite->w();
		height = sprite->h();
	}
	bool draw(int bright = 255, int offset = 0) {
		sprite->pos = pos;
		return sprite->draw(bright, offset);
	}
	bool touch(int l, int r, int y) {
		if (sprite->pos.y - y > 0)   return false;
		if (sprite->pos.y - y < -13) return false;
		int l2 = sprite->pos.x, r2 = l2 + width - 1;
		return r >= l2 && l <= r2;
	}
};

class BrokePad : public Paddle {
public:
	Sprite* sprite[4];
	Uint32 lastTouch = -1;

	BrokePad(int x, int y)
		: Paddle(x, y, BROKEN) {
		sprite[0] = new Sprite("def-brok-0");
		sprite[1] = new Sprite("def-brok-1");
		sprite[2] = new Sprite("def-brok-2");
		sprite[3] = new Sprite("def-brok-3");
		for (int i = 0; i < 4; sprite[i++]->zoom = 0.55f);
		width = sprite[0]->w();
		height = sprite[0]->h();
	}
	bool touch(int l, int r, int y) {
		if (lastTouch != -1) return false;

		if (sprite[0]->pos.y - y > 0)   return false;
		if (sprite[0]->pos.y - y < -13) return false;
		int l2 = sprite[0]->pos.x, r2 = l2 + width - 1;

		if (r >= l2 && l <= r2) {
			lastTouch = SDL_GetTicks();
			Sound::play("breaks");
		}
		
		return false;
	}
	bool draw(int bright = 255, int offset = 0) {
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
};