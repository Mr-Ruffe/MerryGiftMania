#include "engine/AnimatedCharacter.h"

// Destructor of animated character
AnimatedCharacter::~AnimatedCharacter()
{
    animationMap.clear();
}

// Draw function
void AnimatedCharacter::draw() const
{
    // Handle the address to temporary object
    const SDL_Rect &rect = getRect();

    // frame offset
    int col = (animationList[currentFrame]) % spriteCols;
    int row = (animationList[currentFrame]) / spriteCols;

    SDL_Rect srcRect = {col * spriteFrameWidth, row * spriteFrameHeight, spriteFrameWidth, spriteFrameHeight};
    SDL_RenderCopy(sys.getRen(), getTexture(), &srcRect, &rect);
}

// Add animation sequence (integers of sequence)
void AnimatedCharacter::addAnimation(Animation animation, const std::vector<int> &animationVector)
{
    animationMap[animation] = animationVector;
}

// Update the animation state
void AnimatedCharacter::updateAnimationState(Animation animationStateNew)
{
    if (animationState == animationStateNew)
    {
        return;
    }
    animationState = animationStateNew;

    if (animationState == stop)
    {
        animationList = {animationList[currentFrame]};
    }
    else
    {
        if (!animationMap[animationState].empty())
        {
            animationList = animationMap[animationState];
        }
        else
        {
            // If animation doesn't exist for this state -> set to 0
            animationList = {0};
        }
    }
    animationFrameCount = animationList.size();
    currentFrame = 0;
}

bool AnimatedCharacter::isAnimationDone() const
{
    return (currentFrame >= animationFrameCount - 1);
}

void AnimatedCharacter::animate()
{
    counter++;
    // Update draw-state
    if (counter % animationSlowdown == 0)
    {
        currentFrame = (currentFrame + 1) % animationFrameCount;
    }
    // Move character
    switch (animationState)
    {
    case idle:
        break;
    case up:
        moveUp(verticalSpeed);
        break;
    case down:
        moveDown(verticalSpeed);
        break;
    case left:
        moveLeft(horizontalSpeed);
        break;
    case right:
        moveRight(horizontalSpeed);
        break;
    case fall:
        moveDown(fallingSpeed);
        break;
    case stop:
        break;
    case special:
        break;
    }
}

void AnimatedCharacter::setupParameters(int animationSpeedTemp, int horizontalSpeedTemp, int verticalSpeedTemp, int fallingSpeedTemp)
{
    animationSlowdown = animationSpeedTemp;
    horizontalSpeed = horizontalSpeedTemp;
    verticalSpeed = verticalSpeedTemp;
    fallingSpeed = fallingSpeedTemp;
}

AnimatedCharacter::AnimatedCharacter(int x, int y, int frameWidth, int frameHeight, const std::string &path, int scale) : Sprite(x, y, frameWidth, frameHeight, path)
{
    // Query the texture for its size
    spriteFrameWidth = frameWidth * scale;
    spriteFrameHeight = frameHeight * scale;
    int textureWidth, textureHeight;
    SDL_QueryTexture(getTexture(), NULL, NULL, &textureWidth, &textureHeight);
    spriteCols = textureWidth / spriteFrameWidth;
}