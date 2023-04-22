#pragma once
#include "Paddle.h"
#include "../variables.h"

class PadManager {
private:
	static int nextHeight[Global::PAD_NUM];
	static int getNextHeight(PadType type);
public:
	static std::vector<Paddle*> PadArray;
	static void draw(int bright = 255), reset();
	static bool add(int x = 1411, int y = 1411);
	static bool add(int x, int y, PadType type);
};