#include "EnginePch.h"
#include "OBBCollider.h"
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "GeometryHelper.h"

OBBCollider::OBBCollider()
	:BaseCollider(COLLIDER_TYPE::OBB)
{
}

OBBCollider::~OBBCollider()
{
}

void OBBCollider::InitCollider()
{
	_boundingBox.Center = Vec3(0.f, 0.f, 0.f);
	_boundingBox.Extents = Vec3(1.f, 1.f, 1.f);
	_boundingBox.Orientation = Vec4(0.f, 0.f, 0.f, 1.f);
	ShrinkToFit();

	_debugMesh = make_shared<DebugMesh>();
	_debugMesh->Create(GeometryHelper::CreateCube);
}

void OBBCollider::UpdateCollider()
{
	auto transform = GetOwner()->GetTransform();
	Vec3 translate = transform->GetPosition();
	Vec3 scale = transform->GetScale();
	Vec3 rot = transform->GetRotation();
	Vec3 rotRad = Vec3(
		XMConvertToRadians(rot.x),
		XMConvertToRadians(rot.y),
		XMConvertToRadians(rot.z)
		);
	Quaternion q = Quaternion::CreateFromYawPitchRoll(rotRad.y, rotRad.x, rotRad.z);

	_boundingBox.Extents.x = _extentsOrigin.x * scale.x;
	_boundingBox.Extents.y = _extentsOrigin.y * scale.y;
	_boundingBox.Extents.z = _extentsOrigin.z * scale.z;
	_boundingBox.Center = Vec3::Transform(_centerOrigin, Matrix::CreateScale(Vec3(scale)) * Matrix::CreateTranslation(Vec3(translate)));
	_boundingBox.Orientation = q;

	_debugMesh->transfom = Matrix::CreateScale(_boundingBox.Extents);
	_debugMesh->transfom *= Matrix::CreateFromQuaternion(_boundingBox.Orientation);
	_debugMesh->transfom *= Matrix::CreateTranslation(_boundingBox.Center);

	RENDER->PushToDebugMesh(_debugMesh);
}

bool OBBCollider::CheckCollision(shared_ptr<BaseCollider> other)
{
	COLLIDER_TYPE type = other->GetColliderType();

	switch (type)
	{
	case COLLIDER_TYPE::Sphere:
		return _boundingBox.Intersects(dynamic_pointer_cast<SphereCollider>(other)->GetBoundingSphere());
	case COLLIDER_TYPE::AABB:
		return _boundingBox.Intersects(dynamic_pointer_cast<AABBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::OBB:
		return _boundingBox.Intersects(dynamic_pointer_cast<OBBCollider>(other)->GetBoundingBox());
	case COLLIDER_TYPE::Plane:
		return CheckIntersectWithPlane(dynamic_pointer_cast<PlaneCollider>(other)->GetBoundingPlane());
	}

	return false;
}

void OBBCollider::ShrinkToFit()
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

	float xDiff = std::fabs(center.x - xMax.x);
	float yDiff = std::fabs(center.y - yMax.y);
	float zDiff = std::fabs(center.z - zMax.z);

	_extentsOrigin = Vec3(xDiff, yDiff, zDiff);

}

bool OBBCollider::CheckIntersectWithPlane(const BoundingPlane& p)
{
	return false;
}
