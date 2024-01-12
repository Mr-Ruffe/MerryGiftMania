#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "engine/Sprite.h"
#include <vector>
#include <map>

class AnimatedCharacter : public Sprite
{
protected:
    enum Animation
    {
        idle,
        up,
        down,
        left,
        right,
        fall,
        special,
        stop
    };

public:
    // Destructor of animated character
    virtual ~AnimatedCharacter() override;

    // Draw function
    virtual void draw() const;

    // Add animation sequence (integers of sequence)
    void addAnimation(Animation animation, const std::vector<int> &animationVector);

    // Update the animation state
    void updateAnimationState(Animation animationStateNew);

    void animate();

    void setupParameters(int animationSpeedTemp, int horizontalSpeedTemp, int verticalSpeedTemp, int fallingSpeedTemp);

    bool isAnimationDone() const;

protected:
    AnimatedCharacter(int x, int y, int frameWidth, int frameHeight, const std::string &path, int scale);
    Animation animationState = stop;

private:
    std::map<Animation, std::vector<int>> animationMap;
    int counter = 0;

    // Index of current frame in the animation list
    int currentFrame;

    // Animation frame count for current state
    int animationFrameCount = 0;

    // Sprite parameters
    int spriteCols, spriteFrameWidth, spriteFrameHeight;

    // Slowdown: How often animation frame should be changed (fps = FPS/animationSlowdown*60)
    int animationSlowdown;

    // Movement speeds
    int horizontalSpeed, verticalSpeed, fallingSpeed;

    std::vector<int> animationList = {0}; // Animation sequence
};

#endif