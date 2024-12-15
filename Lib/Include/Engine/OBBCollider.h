#pragma once
#include "BaseCollider.h"

class OBBCollider : public BaseCollider
{
public:
	OBBCollider();
	virtual ~OBBCollider();

public:
	virtual void InitCollider() override;
	virtual void UpdateCollider() override;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) override;
	BoundingOrientedBox& GetBoundingBox() { return _boundingBox; }

private:
	void ShrinkToFit();

private:
	// DirectX::Intersects is not work with my BoundingPlane
	// So, Make My Intersects
	bool CheckIntersectWithPlane(const class BoundingPlane& p);

private:
	Vec3 _centerOrigin = Vec3(0.f);
	Vec3 _extentsOrigin = Vec3(1.f, 1.f, 1.f);
	Vec4 _orientationOrigin = Vec4(0.f, 0.f, 0.f, 1.f);
	BoundingOrientedBox _boundingBox;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::OBBCollider;
};

