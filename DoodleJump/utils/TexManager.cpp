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

	SDL_Texture* load(std::string path) {
		SDL_Surface* srf = IMG_Load(path.c_str());
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, srf);
		SDL_FreeSurface(srf);

		if (tex == nullptr) {
			throw(TEXTURE_ERROR);
		}
		else {
			return tex;
		}
	}

	void add(std::string title, std::string path, SDL_Rect src) {
		std::cout << "* Loading image (" << path << "): ";

		try {
			Texture* tmp = new Texture;
			tmp->tex = load(path);
			tmp->src = new SDL_Rect(src);
			if (src.w == 0) {
				SDL_QueryTexture(tmp->tex, NULL, NULL, &tmp->src->w, &tmp->src->h);
			}

			mp[title] = int(collection.size());
			collection.push_back(tmp);

			std::cout << "OK\n";
		} catch (...) {
			std::cout << "FAILED\n";
			throw;
		}
	}

	void fetch(std::string title, SDL_Texture*& tex, SDL_Rect*& src) {
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