#include "EnginePch.h"
#include "BoundingPlane.h"

Vec3 ClosestPoint(const BoundingPlane& plane, const Vec3& point)
{
    float dot = point.Dot(plane.Normal);
    float distance = dot - plane.Distance;
    return point - Vec3(plane.Normal) * distance;
}

bool BoundingPlane::Intersects(const BoundingSphere& sh) const noexcept
{
    Vec3 closestPoint = ClosestPoint(*this, sh.Center);
    float distSq = (sh.Center - closestPoint).LengthSquared();
    float radiusSq = pow(sh.Radius, 2);
    return distSq <= radiusSq;
}

bool BoundingPlane::Intersects(const BoundingBox& box) const noexcept
{
    float pLen = box.Extents.x * fabsf(Normal.x) +
        box.Extents.y * fabsf(Normal.y) +
        box.Extents.z * fabsf(Normal.z);
    
    float dot = Normal.Dot(box.Center);
    float dist = dot - Distance;

    return fabsf(dist) <= pLen;
}
