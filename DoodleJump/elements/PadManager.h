#pragma once
#include "Paddle.h"

class PadManager {
private:
	static int nextHeight;
public:
	static std::deque<Paddle*> PadArray;
	static void draw(int bright = 255), reset();
	static bool add(int x = 1411, int y = 1411, PadType = DEFAULT);
};