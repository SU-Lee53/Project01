#include "EnginePch.h"
#include "Utils.h"
#include "Geometry.h"
#include "InputData.h"

bool Utils::StartsWith(string str, string comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
		return true;

	return false;
}

bool Utils::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
		return true;

	return false;
}

void Utils::Replace(OUT string& str, string comp, string rep)
{
	string temp = str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != string::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	str = temp;
}

void Utils::Replace(OUT wstring& str, wstring comp, wstring rep)
{
	wstring temp = str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	str = temp;
}

std::wstring Utils::ToWString(string value)
{
	return wstring(value.begin(), value.end());
}

std::string Utils::ToString(wstring value)
{
	return string(value.begin(), value.end());
}

string Utils::FileToBuf(ifstream& is)
{
	int fileLength;
	{
		is.seekg(0, ios::end);
		fileLength = is.tellg();
		is.seekg(0, ios::beg);
	}

	string buf;
	buf.resize(fileLength);
	
	is.read(buf.data(), fileLength);

	return buf;
}

//void Utils::MakeCubeGeometry(shared_ptr<Geometry<VertexType>> geometry)
//{
//	float w2 = 0.5f;
//	float h2 = 0.5f;
//	float d2 = 0.5f;
//	vector<VertexType> vtx(24);
//
//	// Front
//	vtx[0] = VertexType{ Vec3(-w2, -h2, -d2), Vec2(0.0f, 1.0f) };
//	vtx[1] = VertexType{ Vec3(-w2, +h2, -d2), Vec2(0.0f, 0.0f) };
//	vtx[2] = VertexType{ Vec3(+w2, +h2, -d2), Vec2(1.0f, 0.0f) };
//	vtx[3] = VertexType{ Vec3(+w2, -h2, -d2), Vec2(1.0f, 1.0f) };
//	// Back
//	vtx[4] = VertexType{ Vec3(-w2, -h2, +d2), Vec2(1.0f, 1.0f) };
//	vtx[5] = VertexType{ Vec3(+w2, -h2, +d2), Vec2(0.0f, 1.0f) };
//	vtx[6] = VertexType{ Vec3(+w2, +h2, +d2), Vec2(0.0f, 0.0f) };
//	vtx[7] = VertexType{ Vec3(-w2, +h2, +d2), Vec2(1.0f, 0.0f) };
//	// Upper
//	vtx[8] = VertexType{ Vec3(-w2, +h2, -d2), Vec2(0.0f, 1.0f) };
//	vtx[9] = VertexType{ Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f) };
//	vtx[10] = VertexType{ Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f) };
//	vtx[11] = VertexType{ Vec3(+w2, +h2, -d2), Vec2(1.0f, 1.0f) };
//	// Lower
//	vtx[12] = VertexType{ Vec3(-w2, -h2, -d2), Vec2(0.0f, 1.0f) };
//	vtx[13] = VertexType{ Vec3(+w2, -h2, -d2), Vec2(0.0f, 0.0f) };
//	vtx[14] = VertexType{ Vec3(+w2, -h2, +d2), Vec2(1.0f, 0.0f) };
//	vtx[15] = VertexType{ Vec3(-w2, -h2, +d2), Vec2(1.0f, 1.0f) };
//	// Left
//	vtx[16] = VertexType{ Vec3(-w2, -h2, +d2), Vec2(0.0f, 1.0f) };
//	vtx[17] = VertexType{ Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f) };
//	vtx[18] = VertexType{ Vec3(-w2, +h2, -d2), Vec2(1.0f, 0.0f) };
//	vtx[19] = VertexType{ Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f) };
//	// Right
//	vtx[20] = VertexType{ Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f) };
//	vtx[21] = VertexType{ Vec3(+w2, +h2, -d2), Vec2(0.0f, 0.0f) };
//	vtx[22] = VertexType{ Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f) };
//	vtx[23] = VertexType{ Vec3(+w2, -h2, +d2), Vec2(1.0f, 1.0f) };
//
//	geometry->SetVertices(vtx);
//
//	vector<uint32> idx(36);
//
//	// Front
//	idx[0] = 0; idx[1] = 1; idx[2] = 2;
//	idx[3] = 0; idx[4] = 2; idx[5] = 3;
//	// Back
//	idx[6] = 4; idx[7] = 5; idx[8] = 6;
//	idx[9] = 4; idx[10] = 6; idx[11] = 7;
//	// Upper
//	idx[12] = 8; idx[13] = 9; idx[14] = 10;
//	idx[15] = 8; idx[16] = 10; idx[17] = 11;
//	// Lower
//	idx[18] = 12; idx[19] = 13; idx[20] = 14;
//	idx[21] = 12; idx[22] = 14; idx[23] = 15;
//	// Left
//	idx[24] = 16; idx[25] = 17; idx[26] = 18;
//	idx[27] = 16; idx[28] = 18; idx[29] = 19;
//	// Right
//	idx[30] = 20; idx[31] = 21; idx[32] = 22;
//	idx[33] = 20; idx[34] = 22; idx[35] = 23;
//
//	geometry->SetIndices(idx);
//}
