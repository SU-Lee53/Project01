#pragma once
#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

public:
	virtual void InitCollider() override;
	virtual void UpdateCollider() override;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) override;

public:
	void SetRadius(float radius) { _radius = radius; }
	BoundingSphere& GetBoundingSphere() { return _boundingSphere; }

private:
	void ShrinkToFit();

private:
	// DirectX::Intersects is not work with my BoundingPlane
	// So, Make My Intersects
	bool CheckIntersectWithPlane(const class BoundingPlane& p);

private:
	float _radius = 1.f;
	BoundingSphere _boundingSphere;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::SphereCollider;
};
