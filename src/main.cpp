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

    // Define the camera to look into our 3d world
    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

    raylib::Model model = LoadModel(ASSETS_PATH"ball-blue.obj");
    raylib::Texture2D texture = LoadTexture(ASSETS_PATH"Textures/colormap.png");

    //DisableCursor();

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        const float frameTime(GetFrameTime());
        if (raylib::Keyboard::IsKeyDown(84)) {
            ballPosition.z += 0.5f;
        }
        UpdateCamera(&camera, CAMERA_ORTHOGRAPHIC);                  // Update camera
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawFrame(camera, model, ballPosition, WHITE);

        EndDrawing();
        physicsEngine.update(frameTime, ballPosition);
    }


    return 0;
}