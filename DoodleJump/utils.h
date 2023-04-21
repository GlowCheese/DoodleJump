#pragma once
#include "Game.h"

// random generator
int Rand(int a, int b);
int Rand(int a, int b, int hash);

// texture manager
class Texture {
public:
	SDL_Texture* tex; SDL_Rect* src;
};

SDL_Rect Rect(int w = 0, int h = 0);
SDL_Rect Rect(int x, int y, int w, int h);

namespace TexManager {
	void add(const char* title, const char* path, SDL_Rect src = Rect());
	void fetch(const char* title, SDL_Texture *&tex, SDL_Rect *&src);
}

namespace Music {
	void add(const char* title, const char* path);

	void setVolume(int perc);
	void play(const char* title);

	void pause(), resume(), stop();
}

namespace Sound {
	void add(const char* title, const char* path);

	void setVolume(int perc);
	void play(const char* title);
}

enum Align { LEFT, RIGHT, CENTER };

class Writer {
private:
	static SDL_Texture* tex;
public:
	static int size;
	static SDL_Color color;
	static void loadTex(std::string message);

	static void write(int x, int y);
	static void write(std::string message, int x, int y, Align align = LEFT);
};
