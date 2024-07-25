// Jolt Physics Library (https://github.com/jrouwe/JoltPhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include "raylib-cpp.hpp"

#include "Physics/BodyActivationListener.hpp"
#include "Physics/Layers.hpp"
#include "Physics/ContactListenerImpl.hpp"

class PhysicsEngine
{
public:
    PhysicsEngine();

    // mutator methods
    void initialise();
    void create_floor(const Vector3 &floor_dimensions,
                      const Vector3 &floor_position);
    void create_ball(float ball_radius,
                     const Vector3 &ball_position,
                     const Vector3 &ball_velocity);
    void start_simulation();
    bool update(float cDeltaTime, Vector3 &sphere_position);
    void cleanup();

private:
    JPH::uint _step{0};
    std::unique_ptr<JPH::PhysicsSystem> _physics_system;
    std::unique_ptr<JPH::TempAllocatorImpl> _temp_allocator;
    std::unique_ptr<JPH::JobSystemThreadPool> _job_system;
    std::unique_ptr<MyBodyActivationListener> _body_activation_listener;
    std::unique_ptr<ContactListenerImpl> _contact_listener;
    std::unique_ptr<BPLayerInterfaceImpl> _broad_phase_layer_interface;
    std::unique_ptr<ObjectVsBroadPhaseLayerFilterImpl>
        _object_vs_broadphase_layer_filter;
    std::unique_ptr<ObjectLayerPairFilterImpl> _object_vs_object_layer_filter;
    JPH::BodyID _sphere_id;
    JPH::BodyID _floor_id;
};