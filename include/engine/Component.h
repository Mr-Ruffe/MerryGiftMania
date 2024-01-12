#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "engine/System.h"
#include "engine/Session.h"

class Component
{
public:
	virtual ~Component() {}
	virtual void mouseDown(int x, int y) {}
	virtual void mouseUp(int x, int y) {}
	virtual void draw() const = 0;
	virtual void keyDown(SDL_Event &event) {}
	virtual void keyUp(SDL_Event &event) {}
	SDL_Rect getRect() const { return rect; }
	virtual void tick() = 0;
	int getCenterX() const { return rect.x + rect.w / 2; }
	int getCenterY() const { return rect.y + rect.h / 2; }
	int getWidth() const { return rect.w; }
	int getHeight() const { return rect.h; }
	bool checkCollision(const Component &other) const
	{
		SDL_Rect rectA = getRect();
		SDL_Rect rectB = other.getRect();

		return (
			rectA.x < rectB.x + rectB.w &&
			rectA.x + rectA.w > rectB.x &&
			rectA.y < rectB.y + rectB.h &&
			rectA.y + rectA.h > rectB.y);
	}
	void setCenterX(int x) { rect.x = x - rect.w / 2; }
	void setCenterY(int y) { rect.y = y - rect.h / 2; }

protected:
	Component(int x, int y, int w, int h) : rect{x - w / 2, y - h, w, h} {}

private:
	SDL_Rect rect;
	Component(Component &) = delete;
	Component &operator=(Component &) = delete;
};

#endif
