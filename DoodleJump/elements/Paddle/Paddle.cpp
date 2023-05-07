#include "../Paddle.h"

bool Paddle::touch(Paddle* another) {
	SDL_Rect a = getRect();
	SDL_Rect b = another->getRect();

	return a.x <= b.x + b.w && a.x + a.w >= b.x
		&& a.y <= b.y + b.h && a.y + a.h >= b.y;
}