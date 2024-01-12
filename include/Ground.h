#ifndef GROUND_H
#define GROUND_H

#include "engine/Sprite.h"
#include "Constants.h"

class Ground : public Sprite
{
public:
	static Ground *getInstance(int y);

	void draw() const;

private:
	Ground(int y) : Sprite(100, y, 200, 20, constants::gResPath + "images/ground.png") {}
};

#endif