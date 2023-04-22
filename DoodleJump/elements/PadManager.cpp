#include "PadManager.h"
#include "../variables.h"

int PadManager::nextHeight[Global::PAD_NUM];
std::vector<Paddle*> PadManager::PadArray;

int PadManager::getNextHeight(PadType type) {
	int index = static_cast<int>(type);

	switch (type) {
	case DEFAULT:
		if (nextHeight[index] <= Global::highest_pad[index] - 40) break;
		nextHeight[index] = Rand(Global::highest_pad[index] - 180, Global::highest_pad[index] - 40);
		break;
	case BROKEN:
		if (nextHeight[index] <= Global::highest_pad[index] - 200) break;
		nextHeight[index] = Rand(Global::highest_pad[index] - 600, Global::highest_pad[index] - 200);
		break;
	}
	
	return nextHeight[index];
}

void PadManager::reset() {
	PadArray.clear();
	for (int i = 0; i < Global::PAD_NUM; i++) {
		nextHeight[i] = 2 * Game::Height();
		Global::highest_pad[i] = 2 * Game::Height();
	}
}

void PadManager::draw(int bright) {
	std::vector<Paddle*> newPadArray;

	for (Paddle* pad : PadArray) {
		if (pad->draw(bright, Global::offset))
			newPadArray.push_back(pad);
	}

	PadArray = newPadArray;
}

bool PadManager::add(int x, int y) {
	bool ok = false;
	ok |= add(x, y, DEFAULT);
	ok |= add(x, y, BROKEN);
	return ok;
}

bool PadManager::add(int x, int y, PadType type) {
	if (y == 1411) y = getNextHeight(type);

	if (y + Global::offset < -30) return false;

	Global::highest_pad[static_cast<int>(type)] = y;

	Paddle* newPad; try {
		switch (type) {
		case DEFAULT:
			newPad = new DefPad(x, y);
			break;
		case BROKEN:
			newPad = new BrokePad(x, y);
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