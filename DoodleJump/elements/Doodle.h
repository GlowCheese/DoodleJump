#pragma once
#include "../components.h"

class Doodle {
private:
	Uint32 lastJump = 0;
public:
	Pair velo;
	Sprite* sprite;
	std::string texname;

	Doodle();
	void handle();
	void update();
	void setPos(int x, int y);
	void setTex(const char* tex);
	void draw(int bright = 255);
};