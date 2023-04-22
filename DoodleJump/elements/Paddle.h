#pragma once
#include "../Game.h"
#include "../utils.h"
#include "../components.h"

enum PadType { DEFAULT = 0, BROKEN = 1 };

class Paddle {
public:
	Pair pos; PadType type;
	Paddle(int x, int y, PadType type) {
		pos = Pair(x, y);
		this->type = type;
	}
	~Paddle() {}
	
	virtual bool touch(int l, int r, int y) { return false; }
	virtual bool draw(int bright = 255, int offset = 0) { return true; }
};

class DefPad : public Paddle {
public:
	Sprite* sprite;
	DefPad(int x, int y)
		: Paddle(x, y, DEFAULT) {
		sprite = new Sprite("def-pad");
		sprite->zoom = 0.6f;
	}
	int len() { return sprite->w(); }
	bool draw(int bright = 255, int offset = 0) {
		sprite->pos = pos;
		return sprite->draw(bright, offset);
	}
	bool touch(int l, int r, int y) {
		if (sprite->pos.y - y > 0)   return false;
		if (sprite->pos.y - y < -13) return false;
		int l2 = sprite->pos.x, r2 = l2 + len() - 1;
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
	}
	int len() { return sprite[0]->w(); }
	bool touch(int l, int r, int y) {
		if (lastTouch != -1) return false;

		if (sprite[0]->pos.y - y > 0)   return false;
		if (sprite[0]->pos.y - y < -13) return false;
		int l2 = sprite[0]->pos.x, r2 = l2 + len() - 1;

		if (r >= l2 && l <= r2) lastTouch = SDL_GetTicks();
		// if doodle touch this broken paddle, we make it fall		
		
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