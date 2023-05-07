#pragma once
#include "../components.h"

class Doodle {
private:
	int angle = 0;
	Uint32 lastJump = 0;
public:
	Pair velo;
	Sprite* sprite;
	Sprite* puca, *njuska;
	std::string texname;
	int lastShoot = -1;

	Doodle();
	~Doodle();
	void handle();
	void update();
	float getAngle();
	float &getX(), &getY();
	void setPos(float x, float y);
	void setTex(std::string tex);
	void draw(int bright = 255);
};