#pragma once
#include "../utils.h"

int Writer::size = 20;
SDL_Texture* Writer::tex;
SDL_Color Writer::color = { 0, 0, 0 };

void Writer::loadTex(std::string message) {
	SDL_Surface* tempSurface = TTF_RenderText_Blended(Game::Font(), message.c_str(), color);
	tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	if (tex == nullptr) throw(TEXTURE_ERROR);
}

void Writer::write(int xpos, int ypos) {
	SDL_Rect* dest = new SDL_Rect;
	dest->x = xpos; dest->y = ypos;
	SDL_QueryTexture(tex, NULL, NULL, &dest->w, &dest->h);
	dest->w = dest->w * size / 300;
	dest->h = dest->h * size / 300;
	SDL_RenderCopy(Game::renderer, tex, NULL, dest);
}

void Writer::write(std::string message, int xpos, int ypos, Align align) {
	loadTex(message);

	int width, height;
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
	width = width * size / 300;
	height = height * size / 300;

	switch (align) {
	case LEFT: write(xpos, ypos); break;
	case CENTER: write(xpos - width / 2, ypos); break;
	case RIGHT: write(xpos - width, ypos); break;
	}
	
	SDL_DestroyTexture(tex);
}