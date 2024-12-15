#include "EnginePch.h"
#include "BoundingPlane.h"

bool BoundingPlane::Intersects(_In_ const BoundingSphere& sh) const noexcept
{
    Vec3 closestPoint = ClosestPoint(*this, sh.Center);
    float distSq = (sh.Center - closestPoint).LengthSquared();
    float radiusSq = pow(sh.Radius, 2);
    return distSq <= radiusSq;
}

bool BoundingPlane::Intersects(_In_ const BoundingBox& box) const noexcept
{
    float pLen = box.Extents.x * fabsf(Normal.x) +
        box.Extents.y * fabsf(Normal.y) +
        box.Extents.z * fabsf(Normal.z);
    
    float dot = Normal.Dot(box.Center);
    float dist = dot - Distance;

    return fabsf(dist) <= pLen;
}

bool BoundingPlane::Intersects(const BoundingOrientedBox& box) const noexcept
{
    // TODO : Fill 
    return false;
}

bool BoundingPlane::Intersects(_In_ const BoundingPlane& p) const noexcept
{
    Vec3 d = Normal.Cross(p.Normal);
    return d.Dot(d) != 0;
}

Vec3 BoundingPlane::ClosestPoint(const BoundingPlane& plane, const Vec3& point)
{
    float dot = point.Dot(plane.Normal);
    float distance = dot - plane.Distance;
    return point - Vec3(plane.Normal) * distance;
}
