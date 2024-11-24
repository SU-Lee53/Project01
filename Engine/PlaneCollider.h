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

public:
	void SetData(float distanceFromOrigin, Vec3 normal)
	{
		_distanceFromOrigin = distanceFromOrigin;
		_normal = normal;
	}

private:
	float _distanceFromOrigin;
	Vec3 _normal;
};

