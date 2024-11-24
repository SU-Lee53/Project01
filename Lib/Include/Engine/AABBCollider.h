#pragma once
#include "BaseCollider.h"

class AABBCollider : public BaseCollider<AABBCollider>
{
public:
	AABBCollider();
	virtual ~AABBCollider();

public:
	void InitCollider() override;
	void UpdateCollider() override;

public:

	void SetData(float center, Vec3 size)
	{
		_center = center;
		_size = size;
	}

private:
	float _center;
	Vec3 _size;


};

