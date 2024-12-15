#pragma once

// Follows DirectXCollision.h style standard
//	-> using SAL annotation https://learn.microsoft.com/ko-kr/cpp/code-quality/understanding-sal?view=msvc-170
//	-> DIFFRENCE : using simplemath vector instead of XMFLOAT3 type

struct BoundingPlane
{
	Vec3 Normal;
	float Distance;

	// Creators

	// Default normal -> look 0,1,0 (upward)
	BoundingPlane() noexcept : Normal(0, 1, 0), Distance(1.f) {}

	BoundingPlane(const BoundingPlane&) = default;
	BoundingPlane& operator=(const BoundingPlane&) = default;

	BoundingPlane(BoundingPlane&&) = default;
	BoundingPlane& operator=(BoundingPlane&&) = default;

	constexpr BoundingPlane(_In_ const Vec3& normal, _In_ const float& distance) noexcept
		: Normal(normal), Distance(distance) {}


	bool Intersects(_In_ const BoundingSphere& sh) const noexcept;
	bool Intersects(_In_ const BoundingBox& box) const noexcept;
	bool Intersects(_In_ const BoundingOrientedBox& box) const noexcept;
	bool Intersects(_In_ const BoundingPlane& box) const noexcept;

	static Vec3 ClosestPoint(const BoundingPlane& plane, const Vec3& point);
};