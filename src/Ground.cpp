#include "Ground.h"

Ground *Ground::getInstance(int y)
{
    return new Ground(y);
}

void Ground::draw() const
{
    const SDL_Rect &rect = getRect();

    // Calculate the number of times the sprite should be repeated in the x-direction
    int repeatCount = (sys.getScreenWidth() / getWidth()) * 2 + 1;

    for (int i = 0; i < repeatCount; ++i)
    {
        SDL_Rect destRect = rect;
        destRect.x = rect.x + i * rect.w;

        SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &destRect);
    }
}
