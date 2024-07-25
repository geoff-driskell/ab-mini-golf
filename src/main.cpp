/*******************************************************************************************
*
*   raylib-cpp [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib-cpp (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib-cpp.hpp"
#include "Physics/PhysicsEngine.hpp"
#include "scene.hpp"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

const int max_columns = 20;



//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    raylib::Window window(screenWidth, screenHeight, "raylib-cpp [core] example - basic window");

    float ballInitialHeight = 15.0f;
    raylib::Vector3 ballPosition(0.0f, ballInitialHeight, 0.0f);
    raylib::Vector3 ballVelocity(0.5f, 0.0f, 0.0f);

    const raylib::Vector3 floorPosition(0.0f, 0.0f, 0.0f);
    const raylib::Vector3 floorDimensions(5.0f, 1.0f, 5.0f);

    PhysicsEngine physicsEngine{};

    physicsEngine.initialise();
    physicsEngine.create_floor(floorDimensions, floorPosition);
    physicsEngine.create_ball(0.84f, ballPosition, ballVelocity);

    physicsEngine.start_simulation();

    raylib::Camera camera;
    camera.position = raylib::Vector3(0.0f, 2.0f, 4.0f);
    camera.target = ballPosition;
    camera.up = raylib::Vector3(0.0f, 1.0f, 0.0f);
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int cameraMode = CAMERA_THIRD_PERSON;

    DisableCursor();

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        const float frameTime(GetFrameTime());
        if (raylib::Keyboard::IsKeyDown(84)) {
            ballPosition.z += 0.5f;
        }
        UpdateCamera(&camera, cameraMode);                  // Update camera
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawFrame(camera, ballPosition, WHITE);

        EndDrawing();
        physicsEngine.update(frameTime, ballPosition);
    }


    return 0;
}