#pragma once
#include "BaseCollider.h"

class SphereCollider : public BaseCollider<SphereCollider>
{
public:
	SphereCollider();
	virtual ~SphereCollider();

public:
	void InitCollider() override;
	void UpdateCollider() override;

public:
	void ShrinkToFit();
	void SetData(Vec3 center, float radius)
	{
		_center = center;
		_radius = radius;
	}

public:
	void CreateDebugMesh();

private:
	Vec3 _center = Vec3{ 0.f,0.f,0.f };
	float _radius = 1.f;

};

