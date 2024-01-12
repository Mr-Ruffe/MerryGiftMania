#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "engine/System.h"
#include "engine/Component.h"

class Sprite : public Component
{
public:
	virtual ~Sprite()
	{
		destroyTexture();
	}

	virtual void draw() const
	{
		// Handle the address to temporary object
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
	}
	virtual void tick() {}

	virtual void moveLeft(int pixels) { setCenterX(getCenterX() - pixels); }
	virtual void moveRight(int pixels) { setCenterX(getCenterX() + pixels); }
	virtual void moveUp(int pixels) { setCenterY(getCenterY() - pixels); }
	virtual void moveDown(int pixels) { setCenterY(getCenterY() + pixels); }
	void destroyTexture() { SDL_DestroyTexture(texture); }

	SDL_Texture *getTexture() const { return texture; }

protected:
	Sprite(int x, int y, int frameWidth, int frameHeight, const std::string &path) : Component(x, y, frameWidth, frameHeight)
	{
		texture = IMG_LoadTexture(sys.getRen(), path.c_str());
	}

private:
	SDL_Texture *texture;
};

#endif