#pragma once
#include "../utils.h"

namespace Sound {
	std::map<std::string, int> mp;
	std::vector<Mix_Chunk*> collection;

	Mix_Chunk* load(std::string path) { return Mix_LoadWAV(path.c_str()); }

	void setVolume(int perc) {
		std::cout << "* Sound volume set to " << perc << ".\n";
		Mix_Volume(-1, perc * 128 / 100);
	}

	void add(std::string title, std::string path) {
		std::cout << "* Loading sound (" << path << "): ";
		Mix_Chunk* tmp = load(path);
		if (tmp == nullptr) {
			std::cout << "FAILED\n";
			throw(AUDIO_ERROR);
		}
		else {
			mp[title] = static_cast<int>(collection.size());
			collection.push_back(tmp);
			std::cout << "OK\n";
		}
	}
	void play(std::string title) {

		if (mp.find(title) == mp.end()) {
			std::cout << "* Playing sound (" << title << "): FAILED\n";
			std::cout << "! Error: No sound named " << title << "\n";
		}
		else {
			Mix_PlayChannel(-1, collection[mp[title]], 0);
		}
	}
};