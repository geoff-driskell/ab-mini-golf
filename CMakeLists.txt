cmake_minimum_required(VERSION 3.14)
project(raylib_cpp_example)

# Add this line, to enable compile command export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.0.2)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# jolt-physics
find_package(JoltPhysics QUIET)
if (NOT JoltPhysics_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        JoltPhysics
        GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
        GIT_TAG v5.0.0
        GIT_SHALLOW 1
        SOURCE_SUBDIR Build
    )
    FetchContent_MakeAvailable(JoltPhysics)
endif()

## Jolt Config

# When turning this option on, the library will be compiled using doubles for
# positions. This allows for much bigger worlds.
set(DOUBLE_PRECISION OFF)

# When turning this option on, the library will be compiled with debug symbols
set(GENERATE_DEBUG_SYMBOLS ON)

# When turning this option on, the library will be compiled in such a way to
# attempt to keep the simulation deterministic across platforms
set(CROSS_PLATFORM_DETERMINISTIC OFF)

# When turning this option on, the library will be compiled with interprocedural
# optimizations enabled, also known as link-time optimizations or link-time code
# generation. Note that if you turn this on you need to use
# SET_INTERPROCEDURAL_OPTIMIZATION() or set(CMAKE_INTERPROCEDURAL_OPTIMIZATION
# ON) to enable LTO specifically for your own project as well. If you don't do
# this you may get an error: /usr/bin/ld: libJolt.a: error adding symbols: file
# format not recognized set(INTERPROCEDURAL_OPTIMIZATION ON)
set(INTERPROCEDURAL_OPTIMIZATION ON)

# When turning this on, in Debug and Release mode, the library will emit extra
# code to ensure that the 4th component of a 3-vector is kept the same as the
# 3rd component and will enable floating point exceptions during simulation to
# detect divisions by zero. Note that this currently only works using MSVC.
# Clang turns Float2 into a SIMD vector sometimes causing floating point
# exceptions (the option is ignored).
set(FLOATING_POINT_EXCEPTIONS_ENABLED OFF)

# Number of bits to use in ObjectLayer. Can be 16 or 32.
set(OBJECT_LAYER_BITS 16)

# Select X86 processor features to use, by default the library compiles with
# AVX2, if everything is off it will be SSE2 compatible.
set(USE_SSE4_1 ON)
set(USE_SSE4_2 ON)
set(USE_AVX ON)
set(USE_AVX2 ON)
set(USE_AVX512 OFF)
set(USE_LZCNT ON)
set(USE_TZCNT ON)
set(USE_F16C ON)
set(USE_FMADD ON)

set(GAME_RESOURCES)

file(GLOB resources ${CMAKE_SOURCE_DIR}/Assets/*)
list(APPEND GAME_RESOURCES ${resources})

# This is the main part:
set(SOURCES 
    src/main.cpp
    src/scene.cpp
    src/Physics/BodyActivationListener.cpp
    src/Physics/ContactListenerImpl.cpp
    src/Physics/GolfBall.cpp
    src/Physics/PhysicsEngine.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp Jolt)
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./Assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable