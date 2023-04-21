#pragma once
#include "../components.h"

class Doodle {
public:
	Pair velo;
	Sprite* sprite;
	std::string texname;

	Doodle();
	void handle();
	void update();
	void setTex(const char* tex);
	void setPos(int x, int y);
	void draw(int bright = 255);
};