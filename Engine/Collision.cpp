#include "EnginePch.h"
#include "Collision.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "AABBCollider.h"

bool Collision::CheckCollision(shared_ptr<SphereCollider> sphere1, shared_ptr<SphereCollider> sphere2)
{
    Vec3 center1 = sphere1->_center;
    Vec3 center2 = sphere2->_center;

    float distanceSq = Vec3::DistanceSquared(center1, center2);
    float sumOfRadiusSq = powf(sphere1->_radius + sphere2->_radius, 2);

    if (distanceSq > sumOfRadiusSq)
        return false;
    else
        return true;

}

bool Collision::CheckCollision(shared_ptr<SphereCollider> sphere, shared_ptr<PlaneCollider> plane)
{
    return false;
}

bool Collision::CheckCollision(shared_ptr<SphereCollider> sphere, shared_ptr<AABBCollider> aabb)
{
    return false;
}

bool Collision::CheckCollision(shared_ptr<PlaneCollider> plane1, shared_ptr<PlaneCollider> aabb2)
{
    return false;
}

bool Collision::CheckCollision(shared_ptr<PlaneCollider> plane, shared_ptr<AABBCollider> aabb)
{
    return false;
}

bool Collision::CheckCollision(shared_ptr<AABBCollider> aabb1, shared_ptr<AABBCollider> aabb2)
{
    return false;
}
