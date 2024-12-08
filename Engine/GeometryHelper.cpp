#include "EnginePch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateSphere(OUT shared_ptr<Geometry<DebugType>> geometry)
{
	float radius = 1.0f; // Radius of Sphere
	uint32 stackCount = 20; // Column Divide
	uint32 sliceCount = 20; // Row Divide

	// Vertices
	vector<DebugType> vtx;

	DebugType v;

	// North(Top)
	v.position = Vec3(0.0f, radius, 0.0f);
	v.color = Color(1.f, 0.f, 0.f, 0.f);

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

			v.color = Color(1.f, 0.f, 0.f, 0.f);

			vtx.push_back(v);
		}
	}

	// South(Bottom)
	v.position = Vec3(0.0f, -radius, 0.0f);
	v.color = Color(1.f, 0.f, 0.f, 0.f);

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

void GeometryHelper::CreateCube(OUT shared_ptr<Geometry<DebugType>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;
	vector<DebugType> vtx(24);

	// Front
	vtx[0] = DebugType{ Vec3(-w2, -h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[1] = DebugType{ Vec3(-w2, +h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[2] = DebugType{ Vec3(+w2, +h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[3] = DebugType{ Vec3(+w2, -h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	// Back
	vtx[4] = DebugType{ Vec3(-w2, -h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[5] = DebugType{ Vec3(+w2, -h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[6] = DebugType{ Vec3(+w2, +h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[7] = DebugType{ Vec3(-w2, +h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	// Upper
	vtx[8] = DebugType{ Vec3(-w2, +h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[9] = DebugType{ Vec3(-w2, +h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[10] = DebugType{ Vec3(+w2, +h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[11] = DebugType{ Vec3(+w2, +h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	// Lower
	vtx[12] = DebugType{ Vec3(-w2, -h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[13] = DebugType{ Vec3(+w2, -h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[14] = DebugType{ Vec3(+w2, -h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[15] = DebugType{ Vec3(-w2, -h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	// Left
	vtx[16] = DebugType{ Vec3(-w2, -h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[17] = DebugType{ Vec3(-w2, +h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[18] = DebugType{ Vec3(-w2, +h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[19] = DebugType{ Vec3(-w2, -h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	// Right
	vtx[20] = DebugType{ Vec3(+w2, -h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[21] = DebugType{ Vec3(+w2, +h2, -d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[22] = DebugType{ Vec3(+w2, +h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };
	vtx[23] = DebugType{ Vec3(+w2, -h2, +d2), Color(1.f, 0.f, 0.f, 0.f) };

	geometry->SetVertices(vtx);

	vector<uint32> idx(36);

	// Front
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	// Back
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	// Upper
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	// Lower
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	// Left
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	// Right
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateGrid(OUT shared_ptr<Geometry<DebugType>> geometry)
{
	int32 sizeX = 20;
	int32 sizeY = 20;

	vector<DebugType> vtx;

	for (int32 z = 0; z < sizeY + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			DebugType v;
			v.position = Vec3(static_cast<float>(x), 0, static_cast<float>(z));
			v.color = Color(1.f, 0.f, 0.f, 0.f);

			vtx.push_back(v);
		}
	}

	geometry->SetVertices(vtx);

	vector<uint32> idx;

	for (int32 z = 0; z < sizeY; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			// [0]
			//  |  \
			// [2] - [1]
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z)+(x));
			// [1] - [2]
			//     \  |
			//       [0]
			idx.push_back((sizeX + 1) * (z)+(x + 1));
			idx.push_back((sizeX + 1) * (z + 1) + (x));
			idx.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(idx);
}
