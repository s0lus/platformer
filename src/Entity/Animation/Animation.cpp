#include "Animation.h"

Animation::Animation()
{
    currentFrame = 0;
    isPlaying = true;
    flip = false;
}

Animation::~Animation()
{}

void Animation::tick(float time)
{
    if (isPlaying) {
        currentFrame += speed * time;
        if (currentFrame > frames.size()) {
            currentFrame -= frames.size();
            if (!loop) {
                isPlaying = false;
                return;
            }
        }
        sprite.setTextureRect(frames[currentFrame]);

        if (flip)
            sprite.setTextureRect(frames_flip[currentFrame]);
    } else {
        sprite.setTextureRect(frames[frames.size() - 1]);
        if (flip)
            sprite.setTextureRect(frames_flip[frames_flip.size() - 1]);
    }
}
