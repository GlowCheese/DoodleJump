#pragma once
#include "../Game.h"
#include "../components.h"

enum ButtonState {
	FREE,
	HOLDING,
	CLICKED
};

class Button {
public:
	const char* title;
	ButtonState state;

	int sz;
	Sprite *off, *on;

	Button(const char* title, int size) : sz(size) {
		state = FREE;
		this->title = title;
		off = new Sprite(title);

		std::string title_on(title);
		title_on += "-on";
		on = new Sprite(title_on.c_str());
	}
	void set_zoom(double z) { off->zoom = on->zoom = z; }
	void set_pos(int x, int y) { off->pos = on->pos = Pair(x, y); }

	bool inside(int x, int y) {
		if (x < on->pos.x_int()) return false;
		if (y < on->pos.y_int()) return false;
		if (x >= on->pos.x_int() + on->w()) return false;
		if (y >= on->pos.y_int() + on->h()) return false;
		return true;
	}
	
	void handle() {
		if (state == CLICKED) return;
		// if clicked, no handle is needed.

		int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
		if (not inside(mouseX, mouseY)) state = FREE;
		else {
			if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				state = HOLDING;
			} else {
				state = FREE;
			}
			if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
				Sound::play("click");
			}
			if (Game::event.type == SDL_MOUSEBUTTONUP) {
				if (Game::event.button.button == SDL_BUTTON_LEFT) {
					state = CLICKED;
				}
			}
		}
	}

	void draw(int bright = 255) {
		if (state == FREE) {
			off->draw(bright);
		} else {
			on->draw(bright);
		}
	}
};