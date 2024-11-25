#pragma once
#include "BaseCollider.h"
#include "BoundingPlane.h"

class PlaneCollider : public BaseCollider
{
public:
	PlaneCollider();
	virtual ~PlaneCollider();

public:
	virtual void UpdateCollider() override;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) override;

	BoundingPlane& GetBoundingPlane() { return _boundingPlane; }

private:
	BoundingPlane _boundingPlane;
};

