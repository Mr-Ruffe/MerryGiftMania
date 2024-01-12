#include "engine/Session.h"
#include <SDL2/SDL.h>
#include "engine/Component.h"
#include "engine/System.h"
#include "Constants.h"
#include <iostream>
#include "Present.h"

using namespace std;

Session ses;

Session::~Session()
{
	for (Component *c : comps)
		delete c;
}

void Session::add(Component *comp)
{
	added.push_back(comp);
}

void Session::remove(Component *comp)
{
	removed.push_back(comp);
}

vector<Component *> Session::getAllComponents() const
{
	return comps;
}

vector<Component *> Session::getComponentsOfType(const type_info &targetType) const
{
	vector<Component *> result;
	for (const auto &component : comps)
	{
		if (typeid(*component) == targetType)
			result.push_back(component);
	}
	return result;
}

void Session::run()
{
	bool quit = false;

	Uint32 tickInterval = 1000 / constants::fps;
	while (!quit)
	{
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				for (Component *c : comps)
					c->mouseDown(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				for (Component *c : comps)
					c->mouseUp(event.button.x, event.button.y);
				break;
			case SDL_KEYDOWN:
				for (Component *c : comps)
					c->keyDown(event);
				break;
			case SDL_KEYUP:
				for (Component *c : comps)
					c->keyUp(event);
				break;
			} // switch
		}	  // inre while

		for (Component *c : comps)
			c->tick();

		for (Component *c : added)
			comps.push_back(c);
		added.clear();

		for (Component *c : removed)
		{
			for (vector<Component *>::iterator i = comps.begin();
				 i != comps.end();)
			{
				if (*i == c)
				{
					i = comps.erase(i);
					delete c;
				}
				else
				{
					i++;
				}
			}
		}
		removed.clear();

		SDL_SetRenderDrawColor(sys.getRen(), 153, 217, 234, 255);
		SDL_RenderClear(sys.getRen());
		for (Component *c : comps)
			c->draw();
		SDL_RenderPresent(sys.getRen());

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
}
