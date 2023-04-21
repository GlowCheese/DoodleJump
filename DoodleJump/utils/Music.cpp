#pragma once
#include "../utils.h"

namespace Music {
	std::map<const char*, int> mp;
	std::vector<Mix_Music*> collection;

	Mix_Music* load(const char* path) { return Mix_LoadMUS(path); }
	void setVolume(int perc) {
		std::cout << "* Music volume set to " << perc << ".\n";
		Mix_VolumeMusic(perc * 128 / 100);
	}

	void stop() { Mix_HaltMusic(); }
	void pause() {
		if (Mix_PausedMusic() != 1) {
			Mix_PauseMusic();
			std::cout << "* Music paused.\n";
		}
	}
	void resume() {
		if (Mix_PausedMusic() == 1) {
			Mix_ResumeMusic();
			std::cout << "* Music resumed.\n";
		}
	}

	void add(const char* title, const char* path) {
		std::cout << "* Loading music (" << path << "): ";
		Mix_Music* tmp = load(path);
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

	void play(const char* title) {
		if (mp.find(title) == mp.end()) {
			std::cout << "* Playing music (" << title << "): FAILED\n";
			std::cout << "! Error: No music named " << title << "\n";
		}
		else {
			Mix_PlayMusic(collection[mp[title]], -1);
		}
	}
}