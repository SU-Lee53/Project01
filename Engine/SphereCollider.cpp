#include "EnginePch.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"

SphereCollider::SphereCollider()
	:BaseCollider(COLLIDER_TYPE::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::InitCollider()
{
	_boundingSphere.Center = Vec3(0.f, 0.f, 0.f);
	_boundingSphere.Radius = 1.f;
	ShrinkToFit();

#ifdef _DEBUG
	//_debugMesh = Geo

#endif
}

void SphereCollider::UpdateCollider()
{
	auto transform = GetOwner()->GetTransform();
	Vec3 translate = transform->GetPosition();
	Vec3 scale = transform->GetScale();

	/*
		TODO : COMPLETE
		current situation
			- after ShrinkToFit(),
				- BoundingSphere.Radius set to max(max(x,y),z)
				- BoundingSphere.Center Set to median of minmax of xyz
			- what to do
				- 2 options
					1. set radius to 1, center to 0,0,0 -> update all size data in _transform
					2. leave BoundingSphere alone -> update only object's transform value in _transfrom
	*/

	_boundingSphere.Center = Vec3::Transform(_centerOrigin, Matrix::CreateTranslation(translate));
	_boundingSphere.Radius = _radiusOrigin * std::max(std::max(scale.x, scale.y), scale.z);
	_transform = Matrix::CreateScale(scale) * Matrix::CreateTranslation(translate);

	//_boundingSphere.Center = GetOwner()->GetTransform()->GetPosition();
	//Vec3 scale = GetOwner()->GetTransform()->GetScale();
	//_boundingSphere.Radius = _radiusOrigin * max(max(scale.x, scale.y), scale.z);
}

bool SphereCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	COLLIDER_TYPE type = other->GetColliderType();

	switch (type)
	{
	case COLLIDER_TYPE::Sphere:
		return _boundingSphere.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case COLLIDER_TYPE::AABB:
		return _boundingSphere.Intersects(dynamic_pointer_cast<AABBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::Plane:
		return CheckIntersectWithPlane(dynamic_pointer_cast<PlaneCollider>(other)->GetBoundingPlane());
	}

	return false;
}

void SphereCollider::ShrinkToFit()
{
	auto meshes = GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetMeshes();

	Vec3 xMin, xMax;
	Vec3 yMin, yMax;
	Vec3 zMin, zMax;

	auto compX = [](VertexType v1, VertexType v2) -> bool
		{
			return v1.position.x < v2.position.x;
		};
	
	auto compY = [](VertexType v1, VertexType v2) -> bool
		{
			return v1.position.x < v2.position.x;
		};
	
	auto compZ = [](VertexType v1, VertexType v2) -> bool
		{
			return v1.position.x < v2.position.x;
		};

	for (const auto& mesh : meshes)
	{
		auto vtxs = mesh->geometry->GetVertices();
		xMin = std::min_element(vtxs.begin(), vtxs.end(), compX)->position;
		xMax = std::max_element(vtxs.begin(), vtxs.end(), compX)->position;

		yMin = std::min_element(vtxs.begin(), vtxs.end(), compY)->position;
		yMax = std::max_element(vtxs.begin(), vtxs.end(), compY)->position;

		zMin = std::min_element(vtxs.begin(), vtxs.end(), compZ)->position;
		zMax = std::max_element(vtxs.begin(), vtxs.end(), compZ)->position;
	}
	
	Vec3 center = Vec3((xMin.x + xMax.x) / 2, (yMin.y + yMax.y) / 2, (zMin.z+ zMax.z) / 2);
	_centerOrigin = center;

	// Radius?
	float xMinDistSq = (xMin - center).LengthSquared();
	float xMaxDistSq = (xMax - center).LengthSquared();
	float xDistBig = std::sqrtf(std::max(xMinDistSq, xMaxDistSq));
	
	float yMinDistSq = (yMin - center).LengthSquared();
	float yMaxDistSq = (yMax - center).LengthSquared();
	float yDistBig = std::sqrtf(std::max(yMinDistSq, yMaxDistSq));
	
	float zMinDistSq = (zMin - center).LengthSquared();
	float zMaxDistSq = (zMax - center).LengthSquared();
	float zDistBig = std::sqrtf(std::max(zMinDistSq, zMaxDistSq));

	_radiusOrigin = std::max(std::max(xDistBig, yDistBig), zDistBig);

}

bool SphereCollider::CheckIntersectWithPlane(const BoundingPlane& p)
{
	Vec3 closestPoint = BoundingPlane::ClosestPoint(p, _boundingSphere.Center);
	float distSq = (_boundingSphere.Center - closestPoint).LengthSquared();
	float radiusSq = pow(_boundingSphere.Radius, 2);
	return distSq <= radiusSq;

	return false;
}
