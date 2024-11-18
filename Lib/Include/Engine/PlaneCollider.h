#pragma once
#include "BaseCollider.h"

class PlaneCollider : public BaseCollider<PlaneCollider>
{
public:
	PlaneCollider();
	virtual ~PlaneCollider();


public:
	void InitCollider() override;
	void UpdateCollider() override;

private:
	float _distanceFromOrigin;
	Vec3 _normal;
};

