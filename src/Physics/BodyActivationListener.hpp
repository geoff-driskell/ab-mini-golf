#ifndef BODYACTIVATIONLISTENER_HPP
#define BODYACTIVATIONLISTENER_HPP

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

// An example activation listener
class MyBodyActivationListener : public JPH::BodyActivationListener
{
public:
    void OnBodyActivated(const JPH::BodyID & /* inBodyID */,
                         JPH::uint64 /* inBodyUserData */) override
    {
    }

    void OnBodyDeactivated(const JPH::BodyID & /* &inBodyID */,
                           JPH::uint64 /* inBodyUserData */) override
    {
    }
};

#endif // BODYACTIVATIONLISTENER_HPP
