#pragma once
#include "../Game.h"
#include "../components.h"

enum ButtonState {
	FREE,
	INSIDE,
	HOLDING,
	CLICKED
};

class Button {
public:
	std::string title;
	ButtonState state;

	int sz;
	Sprite *off, *in, *on;

	Button(const std::string title) {
		state = FREE;
		this->title = title;
		off = new Sprite(title);

		std::string title_in(title);
		title_in += "-in";
		in = new Sprite(title_in);

		std::string title_on(title);
		title_on += "-on";
		on = new Sprite(title_on);


	}
	void set_zoom(double z) { off->zoom = in->zoom = on->zoom = z; }
	void set_pos(int x, int y) { off->pos = in->pos = on->pos = Pair(x, y); }

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
				state = INSIDE;
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
		} else if (state == INSIDE) {
			in->draw(bright);
		} else {
			on->draw(bright);
		}
	}
};