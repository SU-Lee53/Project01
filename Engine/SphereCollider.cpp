#include "EnginePch.h"
#include "SphereCollider.h"

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
}

void SphereCollider::CreateDebugMesh()
{
	auto geometry = _debugMesh->GetGeometry();

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
