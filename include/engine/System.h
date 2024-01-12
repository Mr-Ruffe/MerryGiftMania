#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class System
{
public:
	System();
	~System();

	SDL_Renderer *getRen() const;
	TTF_Font *getFont() const;
	void setFont(const std::string &path, int fontSize);
	void playMusic(const std::string &path);
	void playSoundEffect(const std::string &path);
	int getScreenWidth() const { return screenWidth; }
	int getScreenHeight() const { return screenHeight; }

private:
	SDL_Window *win;
	SDL_Renderer *ren;
	TTF_Font *font;
	Mix_Chunk *music;
	Mix_Chunk *soundEffect;
	int screenWidth = 1280;
	int screenHeight = 720;
	System(System &) = delete;
	System &operator=(System &) = delete;
};

extern System sys;

#endif
