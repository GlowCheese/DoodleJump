#include "../Paddle.h"

bool Paddle::touch(Paddle* another) {
	int x1 = pos.x, y1 = pos.y;
	int w1 = width, h1 = height;

	int x2 = another->pos.x, y2 = another->pos.y;
	int w2 = another->width, h2 = another->height;

	return x1 <= x2 + w2 && x1 + w1 >= x2
		&& y1 <= y2 + h2 && y1 + h1 >= y2;
}