#pragma once
#include "../Game.h"
#include "../components.h"

enum PadType { DEFAULT = 0, BROKEN = 1 };

class Paddle {
public:
	Pair pos; PadType type;
	int width = 0, height = 0;

	~Paddle() {}
	Paddle(int x, int y, PadType type) : pos(x, y), type(type) {}

	virtual bool touch(Paddle* another);
	virtual bool touch(int l, int r, int y, int velo) { return false; }
	virtual bool draw(int bright = 255, int offset = 0) { return false; }
};

class DefPad : public Paddle {
public:
	Sprite* sprite;
	DefPad(int x, int y);
	bool touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};

class BrokenPad : public Paddle {
public:
	Sprite* sprite[4];
	Uint32 lastTouch = -1;

	BrokenPad(int x, int y);
	bool touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};