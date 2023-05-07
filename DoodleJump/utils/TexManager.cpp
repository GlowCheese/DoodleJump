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

	void loadTheme(int theme_id, bool reset) {	
		if (reset) {
			if (Game::selectedTheme == theme_id)
				return;
			for (int _ = 0; _ < 17; _++) {
				delete collection.back();
				collection.pop_back();
			}
		}

		Game::selectedTheme = theme_id;

		std::string theme = "themes/" + Game::theme[theme_id] + '/';
		TexManager::add("bck", theme + "bck.png");
		TexManager::add("left", theme + "left.png");
		TexManager::add("right", theme + "right.png");
		TexManager::add("puca", theme + "puca.png");
		TexManager::add("njuska", theme + "njuska.png");
		TexManager::add("puca-odskok", theme + "puca-odskok.png");
		TexManager::add("left-odskok", theme + "left-odskok.png");
		TexManager::add("right-odskok", theme + "right-odskok.png");
		TexManager::add("pad", theme + "tiles.png", Rect(0, 0, 118, 34));
		TexManager::add("cloud", theme + "tiles.png", Rect(0, 107, 118, 34));
		TexManager::add("brok-0", theme + "tiles.png", Rect(0, 143, 124, 34));
		TexManager::add("brok-1", theme + "tiles.png", Rect(0, 180, 124, 43));
		TexManager::add("brok-2", theme + "tiles.png", Rect(0, 230, 124, 58));
		TexManager::add("brok-3", theme + "tiles.png", Rect(0, 296, 124, 67));
		TexManager::add("spring-0", theme + "tiles.png", Rect(808, 198, 34, 23));
		TexManager::add("spring-1", theme + "tiles.png", Rect(808, 230, 34, 55));
		TexManager::add("horz-pad", theme + "tiles.png", Rect(0, 34, 118, 34));
		TexManager::add("vert-pad", theme + "tiles.png", Rect(0, 71, 118, 34));
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