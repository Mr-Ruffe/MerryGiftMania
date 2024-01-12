#include "Constants.h" //gResPath-contains path to your resources.
#include "engine/System.h"
#include <SDL2/SDL.h>
#include <iostream>

System::System()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow(constants::gameName.c_str(), 30, 30, screenWidth, screenHeight, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
	Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
}

System::~System()
{
	Mix_FreeChunk(music);
	Mix_FreeChunk(soundEffect);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

SDL_Renderer *System::getRen() const
{
	return ren;
}

TTF_Font *System::getFont() const
{
	return font;
}

void System::setFont(const std::string &path, int fontSize)
{
	TTF_Init();
	font = TTF_OpenFont(path.c_str(), fontSize);
}

void System::playMusic(const std::string &path)
{
	music = Mix_LoadWAV(path.c_str());
	Mix_PlayChannel(-1, music, -1);
	if (music == nullptr)
	{
		std::cout << "nullptr" << std::endl;
		return;
	}
	Mix_PlayChannel(-1, music, -1);
}

void System::playSoundEffect(const std::string &path)
{
	soundEffect = Mix_LoadWAV(path.c_str());
	if (soundEffect == nullptr)
	{
		std::cout << "nullptr" << std::endl;
		return;
	}
	Mix_PlayChannel(-1, soundEffect, 0);
}

System sys;
