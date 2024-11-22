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
	virtual void CreateDebugMesh() override;

private:
	Vec3 _center;
	float _radius;

};

