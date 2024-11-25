#pragma once
#include "BaseCollider.h"

class SphereCollider : public BaseCollider
{
public:
	SphereCollider();
	virtual ~SphereCollider();

public:
	virtual void UpdateCollider() override;

public:
	virtual bool CheckCollision(shared_ptr<BaseCollider> other) override;

public:
	void SetRadius(float radius) { _radius = radius; }
	BoundingSphere& GetBoundingSphere() { return _boundingSphere; }

private:
	float _radius = 1.f;
	BoundingSphere _boundingSphere;

};

