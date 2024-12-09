#pragma once
#include "BaseCollider.h"

class AABBCollider : public BaseCollider
{
public:
	AABBCollider();
	virtual ~AABBCollider();

public:
	virtual void InitCollider() override;
	virtual void UpdateCollider() override;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) override;

public:
	BoundingBox& GetBoundingBox() { return _boundingBox; }

private:
	// DirectX::Intersects is not work with my BoundingPlane
	// So, Make My Intersects
	bool CheckIntersectWithPlane(const class BoundingPlane& p);

private:
	BoundingBox _boundingBox;

public:
	//constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::AABBCollider;
};

