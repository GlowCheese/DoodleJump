#pragma once
#include "../Game.h"
#include "../components.h"

enum PadType { DEFAULT = 0, BROKEN = 1, CLOUD = 2, VERTICAL = 3, HORIZONTAL = 4 };

class Paddle {
public:
	Pair pos; PadType type;
	int width = 0, height = 0;

	virtual ~Paddle() {}
	Paddle(int x, int y, PadType type) : pos(x, y), type(type) {}

	virtual bool touch(Paddle* another);
	virtual void update() {}
	virtual int touch(int l, int r, int y, int velo) { return false; }
	virtual bool draw(int bright = 255, int offset = 0) { return false; }
};

class DefPad : public Paddle {
public:
	int spring_offset;
	int last_bounce = -1;

	Sprite* sprite, *spring;

	DefPad(int x, int y);
	int touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};

class VertPad : public Paddle {
public:
	int spring_offset;
	bool going_up = true;
	float padOffset = 0;
	int last_bounce = -1;

	Sprite* sprite, * spring;

	void update();
	VertPad(int x, int y);
	int touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};

class HorzPad : public Paddle {
public:
	int spring_offset;
	bool going_left = true;
	float padOffset = 0;
	int last_bounce = -1;

	Sprite* sprite, * spring;

	void update();
	HorzPad(int x, int y);
	int touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};

class BrokenPad : public Paddle {
public:
	Sprite* sprite[4];
	Uint32 lastTouch = -1;

	BrokenPad(int x, int y);
	int touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};

class CloudPad : public Paddle {
public:
	Sprite* sprite;
	Uint32 lastTouch = -1;

	CloudPad(int x, int y);
	~CloudPad() {
		SDL_DestroyTexture(sprite->tex);
	}
	int touch(int l, int r, int y, int velo);
	bool draw(int bright = 255, int offset = 0);
};