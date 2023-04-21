#pragma once
#include "../Game.h"
#include "../utils.h"
#include "../components.h"

enum PadType { DEFAULT };

class Paddle {
public:
	Sprite* sprite;
	Pair pos; PadType type;
	Paddle(int x, int y, PadType type)
		: pos(x, y), type(type) {}
	
	int len() { return sprite->w(); }
	virtual void draw(int bright = 255, int offset = 0) {}
	virtual bool touch(int l, int r, int y) { return false; }
};

class DefPad : public Paddle {
public:
	DefPad(int x, int y)
		: Paddle(x, y, DEFAULT) {
		sprite = new Sprite("def-pad");
		sprite->zoom = 0.7f;
	}
	void draw(int bright = 255, int offset = 0) {
		sprite->pos = pos;
		sprite->draw(bright, offset);
	}
	bool touch(int l, int r, int y) {
		if (sprite->pos.y - y > 0)   return false;
		if (sprite->pos.y - y < -20) return false;
		int l2 = sprite->pos.x, r2 = l2 + len() - 1;
		return r >= l2 && l <= r2;
	}
};