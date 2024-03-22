#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};

    InitWindow(windowWidth, windowHeight, "My RPG");

    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0, 0};
    const float mapScale{4.f};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{300, 300},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy goblin2{
        Vector2{800, 800},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{400, 400},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[3]{&goblin, &goblin2, &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game over", 50, 50, 50, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 30, 30, 30, WHITE);
        }

        knight.tick(GetFrameTime());

        if (knight.getWorldPos().x < 0 ||
            knight.getWorldPos().y < 0 ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            Rectangle propRec{prop.getCollisionRec(knight.getWorldPos())};
            Rectangle knightRec{knight.getCollisionRec()};

            if (CheckCollisionRecs(propRec, knightRec))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(knight.getWeaponCollisionRec(), enemy->getCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
}