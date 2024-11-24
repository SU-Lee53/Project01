#include "EnginePch.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Model.h"

SphereCollider::SphereCollider()
	: BaseCollider(COLLIDER_TYPE::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::InitCollider()
{
}

void SphereCollider::UpdateCollider()
{
	_transform = GetOwner()->GetTransform()->GetWorld();
}

void SphereCollider::ShrinkToFit()
{
	// TODO : Complete Below

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
		xMax = xMinMax.second->position.x;

		const auto yMinMax = minmax_element(vtx.begin(), vtx.end(), yComp);
		yMin = yMinMax.first->position.y;
		yMax = yMinMax.second->position.y;

		const auto zMinMax = minmax_element(vtx.begin(), vtx.end(), zComp);
		zMin = zMinMax.first->position.z;
		zMax = zMinMax.second->position.z;
	}

	_center = Vec3(
		(xMax + xMin) / 2,
		(yMax + yMin) / 2,
		(zMax + zMin) / 2
	);
}

void SphereCollider::CreateDebugMesh()
{
	_debugMesh = make_shared<ColliderDebugMesh>();

	auto geometry = _debugMesh->GetGeometry();

	// Make Sphere
	{
		float radius = 0.5f; // Radius of Sphere
		uint32 stackCount = 20; // Column Divide
		uint32 sliceCount = 20; // Row Divide

		// Vertices
		vector<DebugType> vtx;

		DebugType v;

		// North(Top)
		v.position = Vec3(0.0f, radius, 0.0f);
		v.color = Color{ 1.f,1.f,1.f,1.f };
		vtx.push_back(v);

		float stackAngle = XM_PI / stackCount;
		float sliceAngle = XM_2PI / sliceCount;

		float deltaU = 1.f / static_cast<float>(sliceCount);
		float deltaV = 1.f / static_cast<float>(stackCount);

		// Compute vertex for each ring
		for (uint32 y = 1; y <= stackCount - 1; ++y)
		{
			float phi = y * stackAngle;

			// Vertex on ring
			for (uint32 x = 0; x <= sliceCount; ++x)
			{
				float theta = x * sliceAngle;
				v.position.x = radius * sinf(phi) * cosf(theta);
				v.position.y = radius * cosf(phi);
				v.position.z = radius * sinf(phi) * sinf(theta);

				v.color = Color{ 1.f,1.f,1.f,1.f };

				vtx.push_back(v);
			}
		}

		// South(Bottom)
		v.position = Vec3(0.0f, -radius, 0.0f);
		v.color = Color{ 1.f,1.f,1.f,1.f };
		vtx.push_back(v);

		geometry->SetVertices(vtx);

		// Indices
		vector<uint32> idx;

		// North index
		for (uint32 i = 0; i <= sliceCount; ++i)
		{
			// [0]
			//  |  \
			// [i+1]-[i+2]
			idx.push_back(0);
			idx.push_back(i + 2);
			idx.push_back(i + 1);
		}

		// Body index
		uint32 ringVertexCount = sliceCount + 1;
		for (uint32 y = 0; y < stackCount - 2; ++y)
		{
			for (uint32 x = 0; x < sliceCount; ++x)
			{
				// [y, x]-[y, x+1]
				//  |       /
				// [y+1, x]
				idx.push_back(1 + (y)*ringVertexCount + (x));
				idx.push_back(1 + (y)*ringVertexCount + (x + 1));
				idx.push_back(1 + (y + 1) * ringVertexCount + (x));
				//          [y, x+1]
				//         /      |
				// [y+1, x]-[y+1,x+1]
				idx.push_back(1 + (y + 1) * ringVertexCount + (x));
				idx.push_back(1 + (y)*ringVertexCount + (x + 1));
				idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
			}
		}

		// South
		uint32 bottomIndex = static_cast<uint32>(vtx.size()) - 1;
		uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
		for (uint32 i = 0; i < sliceCount; ++i)
		{
			// [last+i]-[last+i+1]
			// |        /
			// [bottom]
			idx.push_back(bottomIndex);
			idx.push_back(lastRingStartIndex + i);
			idx.push_back(lastRingStartIndex + i + 1);
		}

		geometry->SetIndices(idx);
	}

	_debugMesh->Create();
}
