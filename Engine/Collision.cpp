#include "EnginePch.h"
#include "Collision.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "AABBCollider.h"

bool Collision::CheckCollision(const SphereCollider& sphere1, const SphereCollider& sphere2)
{
    Vec3 center1 = sphere1._center;
    Vec3 center2 = sphere2._center;

    float distanceSq = Vec3::DistanceSquared(center1, center2);
    float sumOfRadiusSq = powf(sphere1._radius + sphere2._radius, 2);

    if (distanceSq > sumOfRadiusSq)
        return false;
    else
        return true;

}

Vec3 Collision::ClosestPoint(const PlaneCollider& p, const SphereCollider s)
{
    float dot = s._center.Dot(p._normal);
    float distance = dot - p._distanceFromOrigin;
    return s._center - p._normal * distance;
}

bool Collision::CheckCollision(const SphereCollider& sphere, const PlaneCollider& plane)
{
    Vec3 cp = ClosestPoint(plane, sphere);

    float distanceSq = (sphere._center - cp).LengthSquared();
    float radiusSq = powf(sphere._radius, 2);

    return distanceSq <= radiusSq;
}

bool Collision::CheckCollision(const SphereCollider& sphere, const AABBCollider& aabb)
{
    return false;
}

bool Collision::CheckCollision(const PlaneCollider& plane1, const PlaneCollider& aabb2)
{
    return false;
}

bool Collision::CheckCollision(const PlaneCollider& plane, const AABBCollider& aabb)
{
    return false;
}

bool Collision::CheckCollision(const AABBCollider& aabb1, const AABBCollider& aabb2)
{
    return false;
}
