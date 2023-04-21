#pragma once
#include "Game.h"
#include "utils.h"
#include "elements.h"
#include "components.h"

class LoadingScene {
public:
	static void run();
};
class MainMenu {
public:
	static Sprite* menu;
	static Button* start;
	static void init();
	static void handle();
	static void update();
	static void render(int bright = 255);
	static void run();
};
class Jumpppp {
public:
	static Sprite* bck;
	static void init();
	static void handle();
	static void update();
	static void render();
	static void run();
};
class GameOver {
public:
	static Sprite* bck;
	static void init();
	static void handle();
	static void render(int pos, int bright);
	static void run();
};