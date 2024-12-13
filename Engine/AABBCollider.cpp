#include "EnginePch.h"
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "GeometryHelper.h"

AABBCollider::AABBCollider()
	:BaseCollider(COLLIDER_TYPE::AABB)
{
}

AABBCollider::~AABBCollider()
{
}

void AABBCollider::InitCollider()
{
	_boundingBox.Center = Vec3(0.f, 0.f, 0.f);
	_boundingBox.Extents = Vec3(1.f, 1.f, 1.f);
	ShrinkToFit();

	_debugMesh = make_shared<DebugMesh>();
	_debugMesh->Create(GeometryHelper::CreateCube);

}

void AABBCollider::UpdateCollider()
{
	auto transform = GetOwner()->GetTransform();
	Vec3 translate = transform->GetPosition();
	Vec3 scale = transform->GetScale();


	_boundingBox.Extents.x = _extentsOrigin.x * scale.x;
	_boundingBox.Extents.y = _extentsOrigin.y * scale.y;
	_boundingBox.Extents.z = _extentsOrigin.z * scale.z;
	_boundingBox.Center = Vec3::Transform(_centerOrigin, Matrix::CreateScale(Vec3(scale.x, scale.y, scale.z)) * Matrix::CreateTranslation(translate));
	_debugMesh->transfom = Matrix::CreateScale(_boundingBox.Extents) * Matrix::CreateTranslation(_boundingBox.Center);

	RENDER->PushToDebugMesh(_debugMesh);
}

bool AABBCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	COLLIDER_TYPE type = other->GetColliderType();

	switch (type)
	{
	case COLLIDER_TYPE::Sphere:
		return _boundingBox.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case COLLIDER_TYPE::AABB:
		return _boundingBox.Intersects(dynamic_pointer_cast<AABBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::Plane:
		return CheckIntersectWithPlane(dynamic_pointer_cast<PlaneCollider>(other)->GetBoundingPlane());
	}

	return false;
}

void AABBCollider::ShrinkToFit()
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
			return v1.position.y < v2.position.y;
		};

	auto compZ = [](VertexType v1, VertexType v2) -> bool
		{
			return v1.position.z < v2.position.z;
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

	Vec3 center = Vec3((xMin.x + xMax.x) / 2, (yMin.y + yMax.y) / 2, (zMin.z + zMax.z) / 2);
	_centerOrigin = center;

	// Something wrong
	float xMinDistSq = (xMin - center).LengthSquared();
	float xMaxDistSq = (xMax - center).LengthSquared();
	float xDistBig = std::sqrtf(std::max(xMinDistSq, xMaxDistSq));

	float yMinDistSq = (yMin - center).LengthSquared();
	float yMaxDistSq = (yMax - center).LengthSquared();
	float yDistBig = std::sqrtf(std::max(yMinDistSq, yMaxDistSq));

	float zMinDistSq = (zMin - center).LengthSquared();
	float zMaxDistSq = (zMax - center).LengthSquared();
	float zDistBig = std::sqrtf(std::max(zMinDistSq, zMaxDistSq));

	_extentsOrigin.x = xDistBig;
	_extentsOrigin.y = yDistBig;
	_extentsOrigin.z = zDistBig;

}

bool AABBCollider::CheckIntersectWithPlane(const BoundingPlane& p)
{
    float pLen = _boundingBox.Extents.x * fabsf(p.Normal.x) +
        _boundingBox.Extents.y * fabsf(p.Normal.y) +
        _boundingBox.Extents.z * fabsf(p.Normal.z);

    float dot = p.Normal.Dot(_boundingBox.Center);
    float dist = dot - p.Distance;

    return fabsf(dist) <= pLen;
}
