#ifndef LABEL_H
#define LABEL_H

#include "engine/Component.h"

class Label : public Component
{
public:
	static Label *getInstance(int x, int y, int w, int h, const std::string &txt);
	void draw() const;
	std::string getText() const;
	void setText(std::string newText);
	~Label();
	void tick() {}

protected:
	Label(int x, int y, int w, int h, const std::string &txt);

private:
	std::string text;
	SDL_Texture *texture;
};

#endif