#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
};

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;

        if (frame > maxFrames) frame = 0;
    }

    if (Vector2Length(velocity) != 0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        rightLeft = velocity.x < 0.f ? -1.f : 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    Rectangle source{(float)frame * width, 0.0, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    Vector2 origin{0.0, 0.0};

    DrawTexturePro(texture, source, dest, origin, 0, WHITE);
}