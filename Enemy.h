#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    void setTarget(Character* character);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;

private:
    Character* target;
    float damagePerSec{50.f};
    float radius{25.f};
};
