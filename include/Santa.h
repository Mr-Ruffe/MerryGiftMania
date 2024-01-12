#ifndef SANTA_H
#define SANTA_H

#include <vector>

#include "Constants.h"
#include "engine/AnimatedCharacter.h"

class Santa : public AnimatedCharacter
{
public:
	static Santa *getInstance(int x, int y);
	void tick();
	void keyDown(SDL_Event &event);
	void keyUp(SDL_Event &event);

private:
	Santa(int x, int y);
	enum Movement
	{
		horizontal,
		prepForUp,
		prepForDown,
		climbingUp,
		climbingDown,
		sliding,
		hoho,
		wait
	};
	// 0 - horizontal movement, 1 - preparing for up (climb up), 2 - preparing for down (slide/climb down),
	// 3 - ladder movement up, 4 - ladder movement down, 5 - slide movement, 6 - hoho movement, 7 - wait
	Movement movementMode = horizontal;
	int exitUp = 0;
	int exitDown = 0;

	// State logics
	void stateLogics();

	// Verify if ground is reached
	void checkGround(int yCoord, bool goingUp);

	// Sets state to move towards target. Returns false as long as not aligned
	bool isAligned(int targetX);
};

#endif