#include "PadManager.h"
#include "../variables.h"

int PadManager::nextHeight[2];
std::vector<Paddle*> PadManager::PadArray;

int PadManager::getNextHeight(PadType type) {
	int index = type == BROKEN;

	switch (type) {
	case BROKEN:
		if (nextHeight[1] <= Global::highest_pad[1] - 200) break;
		nextHeight[1] = Rand(Global::highest_pad[1] - 600, Global::highest_pad[1] - 200);
		break;
	default:
		if (nextHeight[0] <= Global::highest_pad[0] - 40) break;
		nextHeight[0] = Rand(Global::highest_pad[0] - 180, Global::highest_pad[0] - 40);
		break;
	}
	
	
	return nextHeight[index];
}

void PadManager::reset() {
	PadArray.clear();
	nextHeight[0] = Global::highest_pad[0] = Game::Height();
	nextHeight[1] = Global::highest_pad[1] = Game::Height();
}

void PadManager::draw(int bright) {
	std::vector<Paddle*> newPadArray;

	for (Paddle* pad : PadArray) {
		if (pad->draw(bright, Global::offset)) {
			newPadArray.push_back(pad);
		} else {
			delete pad;
		}
	}

	PadArray = newPadArray;
}

bool PadManager::add(int x, int y) {
	bool ok = false;
	int tmp = Rand(0, 99);

	if (tmp < 80) {
		ok |= add(x, y, DEFAULT);
	}
	else {
		ok |= add(x, y, CLOUD);
	}
	
	ok |= add(x, y, BROKEN);
	return ok;
}

bool PadManager::add(int x, int y, PadType type) {
	if (y == 1411) y = getNextHeight(type);

	if (y + Global::offset < -30) return false;

	Global::highest_pad[type == BROKEN] = y;

	Paddle* newPad; try {
		switch (type) {
		case DEFAULT:
			newPad = new DefPad(x, y);
			break;
		case BROKEN:
			newPad = new BrokenPad(x, y);
			break;
		case CLOUD:
			newPad = new CloudPad(x, y);
			break;
		default:
			newPad = new DefPad(x, y);
			break;
		}
	} catch (...) {
		std::cout << "! Failed to add new paddle.\n";
		throw(ADDING_PADDLE);
	}

	if (x == 1411) {
		while (true) {
			int new_x = Rand(10, Game::Width() - newPad->width - 10);
			newPad->pos = Pair(new_x, y);

			bool ok = true;
			for (Paddle* tmp : PadArray) {
				if (newPad->touch(tmp)) {
					ok = false;
					break;
				}
			}

			if (ok) { break; }
		}
	}

	PadArray.push_back(newPad);
	return true;
}