#pragma once
#include "../utils.h"


SDL_Rect Rect(int w, int h) {
	return SDL_Rect({ 0, 0, w, h });
}
SDL_Rect Rect(int x, int y, int w, int h) {
	return SDL_Rect({ x, y, w, h });
}

namespace TexManager {
	std::map<std::string, int> mp;
	std::vector<Texture*> collection;

	void add(const char* title, const char* path, SDL_Rect src) {
		std::cout << "* Loading image (" << path << "): ";

		Texture* tmp = new Texture;
		SDL_Surface* srf = IMG_Load(path);
		tmp->tex = SDL_CreateTextureFromSurface(Game::renderer, srf);

		if (tmp->tex == nullptr) {
			std::cout << "FAILED\n";
			throw(TEXTURE_ERROR);
		}
		else {
			tmp->src = new SDL_Rect(src);
			if (src.w == 0) {
				tmp->src->w = srf->w;
				tmp->src->h = srf->h;
			}

			mp[title] = int(collection.size());
			collection.push_back(tmp);
			std::cout << "OK\n";
		}
	}

	void fetch(const char* title, SDL_Texture*& tex, SDL_Rect*& src) {
		if (mp.find(title) == mp.end()) {
			std::cout << "* Fetching texture (" << title << "): FAILED\n";
			std::cout << "! Error: No texture named " << title << "\n";
			throw(TEXTURE_ERROR);
		}
		else {
			Texture* tmp = collection[mp[title]];
			tex = tmp->tex; src = tmp->src;
		}
	}
}