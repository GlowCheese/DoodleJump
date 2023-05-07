#include "Bullet.h"
#include "../variables.h"
#include "../components.h"

struct Pellet {
	int angle;
	float vx, vy;
	bool visible;
	Sprite* sprite;

	float& x() { return sprite->pos.x; }
	float& y() { return sprite->pos.y; }

	Pellet(int x, int y, int angle) : visible(true) {
		sprite = new Sprite(Game::getThemeIMG("bullet"));
		this->x() = x; vy = -22 * cos(angle*acos(-1)/180);
		this->y() = y; vx =  22 * sin(angle*acos(-1)/180);
		sprite->zoom = 0.6f;
	}
	~Pellet() { delete sprite; }
};

std::vector<Pellet*> BulArray;
void Bullet::add(int x, int y, float angle) {
	BulArray.push_back(new Pellet(x, y, angle));
}

void Bullet::update() {
	for (Pellet *&bul : BulArray) {
		bul->sprite->pos.x += bul->vx;
		bul->sprite->pos.y += bul->vy;
		if (++bul->angle == 360) bul->angle = 0;
		bul->vy += 1.0f;
	}
}

void Bullet::draw() {
	std::vector<Pellet*> newBulArray;
	for (Pellet *&bul : BulArray) {
		if (!bul->visible || bul->y() >= Game::Height()) {
			delete bul;
		} else {
			bul->sprite->draw(255, Global::offset, bul->angle);
			newBulArray.push_back(bul);
		}
	}
	BulArray = newBulArray;
}