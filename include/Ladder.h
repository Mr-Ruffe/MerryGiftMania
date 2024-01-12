#ifndef LADDER_H
#define LADDER_H

#include "engine/Sprite.h"
#include "Constants.h"

class Ladder : public Sprite
{
public:
	static Ladder *getInstance(int x, int y) { return new Ladder(x, y); }

	int getTopExit() const { return getCenterY() - getHeight() / 2 + 12; }
	int getBottomExit() const { return getCenterY() + getHeight() / 2; }

private:
	Ladder(int x, int y) : Sprite(x, y, 112, 287, constants::gResPath + "images/ladder.png") {}
};
#endif