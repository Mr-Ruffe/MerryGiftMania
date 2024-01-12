#ifndef SLIDE_H
#define SLIDE_H

#include "engine/Sprite.h"
#include "Constants.h"

class Slide : public Sprite
{
public:
	static Slide *getInstance(int x, int y) { return new Slide(x, y); }
	int getBottomExit() const { return getCenterY() + getHeight() / 2; }

private:
	Slide(int x, int y) : Sprite(x, y, 112, 287, constants::gResPath + "images/slide.png") {}
};

#endif