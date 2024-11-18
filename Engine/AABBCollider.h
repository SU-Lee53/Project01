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

private:
	float _center;
	Vec3 _size;

};

