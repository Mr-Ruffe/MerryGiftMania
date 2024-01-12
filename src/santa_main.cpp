#include "engine/Component.h"
#include "engine/Session.h"
#include "engine/System.h"
#include "engine/Label.h"

#include "Constants.h"
#include "Santa.h"
#include "Present.h"
#include "GiftCounter.h"
#include "Ladder.h"
#include "Slide.h"
#include "Timer.h"
#include "Wall.h"
#include "Ground.h"

void setScene()
{
	// Static
	Ground *ground1 = Ground::getInstance(720);
	ses.add(ground1);
	Ground *ground2 = Ground::getInstance(720 - 275);
	ses.add(ground2);
	Ground *ground3 = Ground::getInstance(720 - 550);
	ses.add(ground3);
	Wall *wall1 = Wall::getInstance(600, 720);
	ses.add(wall1);
	Wall *wall2 = Wall::getInstance(600, 720 - 275);
	ses.add(wall2);
	Ladder *ladder1 = Ladder::getInstance(700, 700);
	ses.add(ladder1);
	Ladder *ladder2 = Ladder::getInstance(1000, 700 - 275);
	ses.add(ladder2);
	Slide *slide1 = Slide::getInstance(500, 700);
	ses.add(slide1);
	Slide *slide2 = Slide::getInstance(200, 700 - 275);
	ses.add(slide2);

	// Dynamic
	Santa *santa = Santa::getInstance(1000, 700);
	ses.add(santa);
	Present *present1 = Present::getInstance(50, 700);
	ses.add(present1);
	Present *present2 = Present::getInstance(800, 700);
	ses.add(present2);
	Present *present3 = Present::getInstance(800, 700 - 275);
	ses.add(present3);
	Present *present4 = Present::getInstance(1100, 700 - 550);
	ses.add(present4);
	Present *present5 = Present::getInstance(50, 700 - 550);
	ses.add(present5);

	// Overlay
	Label *countLabel = Label::getInstance(600, 50, 50, 35, "0/0");
	ses.add(countLabel);
	GiftCounter *giftCounter = GiftCounter::getInstance(countLabel);
	ses.add(giftCounter);
	Label *timerLabel = Label::getInstance(1200, 50, 100, 35, "0:00:00");
	ses.add(timerLabel);
	Timer *timer = Timer::getInstance(timerLabel);
	ses.add(timer);

	// System setup
	sys.setFont(constants::gResPath + "fonts/arial.ttf", 16);
	sys.playMusic(constants::gResPath + "sounds/music.mp3");
}

int main(int argc, char *argv[])
{
	setScene();
	ses.run();
	return 0;
}
