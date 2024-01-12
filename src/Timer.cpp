#include "Timer.h"

#include <SDL2/SDL.h>

// Factory constructor
Timer *Timer::getInstance(Label *labelRef)
{
    return new Timer(labelRef);
}

// Tick function
void Timer::tick()
{
    if (running)
    {
        elapsedTime = SDL_GetTicks() - startTime;
        // Calculate minutes, seconds, and milliseconds
        int minutes = elapsedTime / 60000;
        int seconds = (elapsedTime / 1000) % 60;
        int milliseconds = elapsedTime % 1000;

        label->setText(formulateTimeString(minutes, seconds, milliseconds));
    }
}

// Called when game is won
void Timer::gameWon()
{
    running = false;
}

// Formulates the label time-string
std::string Timer::formulateTimeString(int minutes, int seconds, int milliseconds) const
{
    return std::to_string(minutes) + ":" +
           (seconds < 10 ? "0" : "") + std::to_string(seconds) + "." +
           (milliseconds < 100 ? "0" : "") +
           std::to_string(milliseconds / 10);
}