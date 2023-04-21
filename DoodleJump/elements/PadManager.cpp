#include "PadManager.h"
#include "../variables.h"

int PadManager::nextHeight = -1;
std::deque<Paddle*> PadManager::PadArray;

void PadManager::reset() {
	PadArray.clear();
	Global::offset = 0;
	Global::highest_pad = Game::Height();
}

void PadManager::draw(int bright) {
	for (Paddle* pad : PadArray) {
		pad->draw(bright, Global::offset);
	}
}

bool PadManager::add(int x, int y, PadType type) {
	if (x == 1411) x = Rand(10, Game::Width() - Global::PAD_LENGTH - 10);
	if (y == 1411) y = nextHeight;

	if (y + Global::offset < -30) return false;

	Global::highest_pad = y;
	nextHeight = Rand(Global::highest_pad - 180, Global::highest_pad - 40);

	try {
		switch (type) {
		case DEFAULT:
			PadArray.push_back(new DefPad(x, y));
			break;
		}

	}
	catch (...) {
		std::cout << "! Failed to add new paddle.\n";
		throw(ADDING_PADDLE);
	}

	return true;
}