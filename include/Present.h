#ifndef PRESENT_H
#define PRESENT_H

#include "engine/Sprite.h"
#include "Constants.h"

class Present : public Sprite
{
public:
	static Present *getInstance(int x, int y) { return new Present(x, y); }

private:
	Present(int x, int y) : Sprite(x, y, 50, 62, constants::gResPath + "images/present.png") {}
};

#endif