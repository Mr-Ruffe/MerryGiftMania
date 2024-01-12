#include "Santa.h"
#include "Present.h"
#include "Ladder.h"
#include "Slide.h"
#include "Wall.h"
#include "engine/Component.h"
#include <iostream>

// Factory constructor
Santa *Santa::getInstance(int x, int y) { return new Santa(x, y); }

// Constructor
Santa::Santa(int x, int y) : AnimatedCharacter(x, y, 100, 100, constants::gResPath + "images/santa_sprite_transparent.png", 4)
{
    addAnimation(idle, {0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 3, 4, 3, 2, 1});
    addAnimation(left, {10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    addAnimation(right, {20, 21, 22, 23, 24, 25, 26, 27, 28, 29});
    addAnimation(special, {5, 6, 7, 8, 9, 8, 7, 8, 9, 8, 7, 8, 9, 8, 7, 6}); // Hoho animation
    addAnimation(fall, {35, 36, 37, 38});                                    // Sliding down animation
    addAnimation(up, {30, 31, 32, 33, 34, 33, 32, 31});                      // Climbing up animation
    addAnimation(down, {30, 31, 32, 33, 34, 33, 32, 31});                    // Climbing down animation

    // Set speed parameters: (animationSpeed, horizontalSpeed, verticalSpeed, falling/slidingSpeed)
    setupParameters(12, 1, 1, 2);

    updateAnimationState(idle);
}

// Tick function
void Santa::tick()
{
    stateLogics();
    animate();
}

// When a button is pressed on the keyboard
void Santa::keyDown(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            // Verify if climb is possible
            if (movementMode == horizontal)
                movementMode = prepForUp;
            // Verify if climbing
            else if (movementMode == climbingUp || movementMode == climbingDown)
            {
                movementMode = climbingUp;
                updateAnimationState(up);
            }
            break;

        case SDLK_DOWN:
            // Verify if slide is possible
            if (movementMode == horizontal)
                movementMode = prepForDown;
            // Verify if climbing
            else if (movementMode == climbingUp || movementMode == climbingDown)
            {
                movementMode = climbingDown;
                updateAnimationState(down);
            }
            break;

        case SDLK_LEFT:
            if (movementMode == horizontal)
                updateAnimationState(left);
            break;

        case SDLK_RIGHT:
            if (movementMode == horizontal)
                updateAnimationState(right);
            break;
        }
    }
}

// When a button is released on the keyboard
void Santa::keyUp(SDL_Event &event)
{
    if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
        {
            if (movementMode == 7)
                movementMode = horizontal;
            // Returning to idle from left/right walk
            if (movementMode == horizontal)
                updateAnimationState(idle);
        }
        else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
        {
            // Stopping mid-climbing
            if (movementMode == 3 || movementMode == 4)
                updateAnimationState(stop);
            // Stopping when adjusting to slide/climb
            else if (movementMode == 1 || movementMode == 2)
            {
                updateAnimationState(idle);
                movementMode = horizontal;
            }
        }
    }
}

// State logics
void Santa::stateLogics()
{
    if (movementMode == horizontal || movementMode == prepForUp || movementMode == prepForDown)
    {
        // itterate through presents and check if coliding
        for (auto &component : ses.getComponentsOfType(typeid(Present)))
        {
            if (checkCollision(*component))
            {
                // if coliding: start hoho-animation and remove present
                movementMode = hoho;
                updateAnimationState(special);
                ses.remove(component);
                sys.playSoundEffect(constants::gResPath + "sounds/hohoho.mp3");
            }
        }

        for (auto &component : ses.getComponentsOfType(typeid(Wall)))
        {
            if (checkCollision(*component))
            {
                // if coliding: stop animation and movement (goto wait-state)
                SDL_Rect componentRect = component->getRect();
                if (getCenterX() > componentRect.x)
                    setCenterX(getWidth() / 2 + componentRect.x + componentRect.w);
                else
                    setCenterX(componentRect.x - getWidth() / 2);
                movementMode = wait;
                updateAnimationState(stop);
            }
        }

        // If x is outside map : jump to the right side
        if (getCenterX() < -getWidth() / 2 || getCenterX() > sys.getScreenWidth() + getWidth() / 2)
        {
            setCenterX(sys.getScreenWidth() + getWidth() / 2);
        }
    }
    switch (movementMode)
    {
    case horizontal:
        break;
    case prepForUp: // Preparing for ladder
        // itterate through ladders and check if coliding + center above. Use center as target in isAligned
        for (auto &component : ses.getComponentsOfType(typeid(Ladder)))
        {
            if (component->getCenterY() < getCenterY() && checkCollision(*component))
            {
                if (isAligned(component->getCenterX()))
                {
                    updateAnimationState(up);
                    movementMode = climbingUp;
                    Ladder *ladderComponent = dynamic_cast<Ladder *>(component);
                    exitUp = ladderComponent->getTopExit();
                    exitDown = ladderComponent->getBottomExit();
                }
                break;
            }
        }
        break;
    case prepForDown: // Preparing for slide/ladder down
        // itterate through slides and check if coliding + center below. Use center as target in isAligned
        for (auto &component : ses.getComponentsOfType(typeid(Slide)))
        {
            if (component->getCenterY() > getCenterY() && checkCollision(*component))
            {
                if (isAligned(component->getCenterX()))
                {
                    updateAnimationState(fall);
                    movementMode = sliding;
                    Slide *slideComponent = dynamic_cast<Slide *>(component);
                    exitDown = slideComponent->getBottomExit();
                }
                break;
            }
        }
        // itterate through ladders and check if coliding + center above. Use center as target in isAligned
        for (auto &component : ses.getComponentsOfType(typeid(Ladder)))
        {
            if (component->getCenterY() > getCenterY() && checkCollision(*component))
            {
                if (isAligned(component->getCenterX()))
                {
                    updateAnimationState(down);
                    movementMode = climbingDown;
                    Ladder *ladderComponent = dynamic_cast<Ladder *>(component);
                    exitUp = ladderComponent->getTopExit();
                    exitDown = ladderComponent->getBottomExit();
                }
                break;
            }
        }
        break;
    case climbingUp: // Climbing up
        // Verify if top is reached when climbing up
        checkGround(exitUp, true);
        break;
    case climbingDown: // Climbing down
        // Verify if bottom is reached when climbing down
        checkGround(exitDown, false);
        break;
    case sliding: // Sliding down
        // Verify if bottom is reached when sliding down
        checkGround(exitDown, false);
        break;

    case hoho: // Doing the ho-ho
        if (isAnimationDone())
        {
            movementMode = horizontal;
            updateAnimationState(idle);
        }
        break;
    case wait: // wait-state
        break;
    }
}

// Stop when yCoord is reached
void Santa::checkGround(int yCoord, bool goingUp)
{
    int bottomCoordinate = getCenterY() + getHeight() / 2;
    if ((!goingUp && bottomCoordinate > yCoord) || (goingUp && bottomCoordinate < yCoord))
    {
        setCenterY(yCoord - getHeight() / 2);
        updateAnimationState(idle);
        movementMode = horizontal;
        exitUp = 0;
        exitDown = 0;
    }
}

// Sets state to move towards target. Returns false as long as not aligned
bool Santa::isAligned(int targetX)
{
    int margin = 75;
    int targetOffset = getCenterX() - targetX;
    if (abs(targetOffset) < margin)
    {
        if (abs(targetOffset) < 1)
        {
            setCenterX(targetX);
            return true;
        }
        else if (targetOffset > 0)
            updateAnimationState(left);
        else
            updateAnimationState(right);
    }
    else
    {
        movementMode = horizontal; // if outside target: reset to horizontal movement
        updateAnimationState(idle);
    }
    return false;
}