#ifndef GIFT_COUNTER_H
#define GIFT_COUNTER_H

#include "Constants.h"
#include "engine/Sprite.h"
#include "engine/Label.h"

class GiftCounter : public Sprite
{
public:
	static GiftCounter *getInstance(Label *labelRef) { return new GiftCounter(labelRef); }

	void tick();

	int countCurrentPresents() const;

	void updateCount();

private:
	GiftCounter(Label *labelRef);
	int amountOfPresents;
	Label *label;
};

#endif