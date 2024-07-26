#include "scene.hpp"

void drawFrame(const raylib::Camera& camera, raylib::Model& model, const raylib::Vector3& ballPosition, const raylib::Color& ballColor) {
    BeginMode3D(camera);
        DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, GREEN); // Draw ground
        DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
        DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
        DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
        DrawGrid(10.0f, 10.0f);
        DrawModel(model, ballPosition, 1.0f, WHITE);
    EndMode3D();
}
