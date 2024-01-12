#ifndef WALL_H
#define WALL_H

#include "engine/Sprite.h"
#include "Constants.h"

class Wall : public Sprite
{
public:
	static Wall *getInstance(int x, int y) { return new Wall(x, y); }

private:
	Wall(int x, int y) : Sprite(x, y, 20, 275, constants::gResPath + "images/wall.png") {}
};

#endif