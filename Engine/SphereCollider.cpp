#include "EnginePch.h"
#include "SphereCollider.h"
#include "AABBCollider.h"
#include "PlaneCollider.h"
#include "Collision.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"

SphereCollider::SphereCollider()
{
	_colliderType = COLLIDER_TYPE::Sphere;
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::ShrinkToFit()
{
	auto meshes = GetOwner()->GetComponent<MeshRenderer>()->GetModel()->GetMeshes();

	float xMin = FLT_MAX;
	float xMax = FLT_MIN;
	float yMin = FLT_MAX;
	float yMax = FLT_MIN;
	float zMin = FLT_MAX;
	float zMax = FLT_MIN;

	auto xComp = [](const VertexType v1, const VertexType v2)
		{
			return v1.position.x < v2.position.x;
		};
	
	auto yComp = [](const VertexType v1, const VertexType v2)
		{
			return v1.position.y < v2.position.y;
		};
	
	auto zComp = [](const VertexType v1, const VertexType v2)
		{
			return v1.position.z < v2.position.z;
		};

	for (const auto& mesh : meshes)
	{
		auto vtx = mesh->geometry->GetVertices();

		const auto xMinMax = minmax_element(vtx.begin(), vtx.end(), xComp);
		xMin = xMinMax.first->position.x;
		xMin = xMinMax.second->position.x;
		
		const auto yMinMax = minmax_element(vtx.begin(), vtx.end(), yComp);
		yMin = yMinMax.first->position.y;
		yMin = yMinMax.second->position.y;
		
		const auto zMinMax = minmax_element(vtx.begin(), vtx.end(), zComp);
		zMin = zMinMax.first->position.z;
		zMin = zMinMax.second->position.z;
	}

	_center = Vec3(
		(xMax + xMin) / 2,
		(yMax + yMin) / 2,
		(zMax + zMin) / 2
	);




}

bool SphereCollider::CheckCollision(shared_ptr<Collider> other)
{
	auto type = other->_colliderType;

	switch (type)
	{
	case COLLIDER_TYPE::AABB:
		return Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<AABBCollider>(other));
		
	case COLLIDER_TYPE::Plane:
		return Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<PlaneCollider>(other));

	case COLLIDER_TYPE::Sphere:
		return Collision::CheckCollision(shared_from_this(), dynamic_pointer_cast<SphereCollider>(other));

	default:
		assert(false);
	}

	assert(false);
}
