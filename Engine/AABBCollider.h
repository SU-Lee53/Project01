#pragma once
#include "BaseCollider.h"

class AABBCollider : public BaseCollider
{
public:
	AABBCollider();
	virtual ~AABBCollider();

public:
	virtual void UpdateCollider() override;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) override;

public:
	BoundingBox& GetBoundingBox() { return _boundingBox; }

private:
	BoundingBox _boundingBox;

};

