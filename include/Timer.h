#ifndef TIMER_H
#define TIMER_H

#include <string>

#include "engine/Component.h"
#include "engine/Label.h"

class Timer : public Component
{
public:
	static Timer *getInstance(Label *labelRef);

	void draw() const {}
	void tick();

	void gameWon();

private:
	Timer(Label *labelRef) : Component(0, 0, 0, 0), label(labelRef) {}
	std::string formulateTimeString(int minutes, int seconds, int milliseconds) const;

	Label *label;
	Uint32 startTime = 0;
	Uint32 elapsedTime = 0;
	bool running = true;
};

#endif