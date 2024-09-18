#include "EnginePch.h"
#include "Utils.h"

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

void Utils::MakeQuadGeometry(OUT shared_ptr<VAO>& vao)
{
	//auto vertex = vao.GetVBO<BUFFER_TYPE::Vertex>();
	//auto index = vao.GetVBO<BUFFER_TYPE::Index>();
	//auto color = vao.GetVBO<BUFFER_TYPE::Color>();
	
	vector<glm::vec3> vtx;
	vtx.resize(4);

	vector<RGB> color;
	color.resize(4);

	vtx[0] = glm::vec3(-0.5f, -0.5f, 0.f);
	color[0].rgb = glm::vec3(1.0f, 0.0f, 0.0f);

	vtx[1] = glm::vec3(-0.5f, 0.5f, 0.f);
	color[1].rgb = glm::vec3(0.0f, 1.0f, 0.0f);

	vtx[2] = glm::vec3(0.5f, -0.5f, 0.f);
	color[2].rgb = glm::vec3(0.0f, 0.0f, 1.0f);

	vtx[3] = glm::vec3(0.5f, 0.5f, 0.f);
	color[3].rgb = glm::vec3(1.0f, 0.0f, 1.0f);

	vector<unsigned int> idx = { 2, 1, 0, 2, 3, 1 };

	vao->GetVBO<BUFFER_TYPE::Vertex>().SetBuffer(vtx);
	vao->GetVBO<BUFFER_TYPE::Color>().SetBuffer(color);
	vao->GetVBO<BUFFER_TYPE::Index>().SetBuffer(idx);

}

void Utils::MakeCubeGeometry(OUT shared_ptr<class VAO>& vao)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;
	vector<glm::vec3> vtx(24);
	vector<RGB> color(24);
	vector<unsigned int> idx(36);

	// Vertex
	{
		vtx[0] = glm::vec3(-w2, -h2, -d2);
		vtx[1] = glm::vec3(-w2, +h2, -d2);
		vtx[2] = glm::vec3(+w2, +h2, -d2);
		vtx[3] = glm::vec3(+w2, -h2, -d2);

		vtx[4] = glm::vec3(-w2, -h2, +d2);
		vtx[5] = glm::vec3(+w2, -h2, +d2);
		vtx[6] = glm::vec3(+w2, +h2, +d2);
		vtx[7] = glm::vec3(-w2, +h2, +d2);

		vtx[8] = glm::vec3(-w2, +h2, -d2);
		vtx[9] = glm::vec3(-w2, +h2, +d2);
		vtx[10] = glm::vec3(+w2, +h2, +d2);
		vtx[11] = glm::vec3(+w2, +h2, -d2);

		vtx[12] = glm::vec3(-w2, -h2, -d2);
		vtx[13] = glm::vec3(+w2, -h2, -d2);
		vtx[14] = glm::vec3(+w2, -h2, +d2);
		vtx[15] = glm::vec3(-w2, -h2, +d2);

		vtx[16] = glm::vec3(-w2, -h2, +d2);
		vtx[17] = glm::vec3(-w2, +h2, +d2);
		vtx[18] = glm::vec3(-w2, +h2, -d2);
		vtx[19] = glm::vec3(-w2, -h2, -d2);

		vtx[20] = glm::vec3(+w2, -h2, -d2);
		vtx[21] = glm::vec3(+w2, +h2, -d2);
		vtx[22] = glm::vec3(+w2, +h2, +d2);
		vtx[23] = glm::vec3(+w2, -h2, +d2);
	}

	// Color
	{
		color[0].rgb = glm::vec3(1.f, 0.f, 0.f);
		color[1].rgb = glm::vec3(0.f, 1.f, 0.f);
		color[2].rgb = glm::vec3(0.f, 0.f, 1.f);
		color[3].rgb = glm::vec3(1.f, 0.f, 1.f);

		color[4].rgb = glm::vec3(1.f, 0.f, 0.f);
		color[5].rgb = glm::vec3(0.f, 1.f, 0.f);
		color[6].rgb = glm::vec3(0.f, 0.f, 1.f);
		color[7].rgb = glm::vec3(0.f, 1.f, 1.f);

		color[8].rgb = glm::vec3(1.f, 0.f, 0.f);
		color[9].rgb = glm::vec3(0.f, 1.f, 0.f);
		color[10].rgb = glm::vec3(0.f, 0.f, 1.f);
		color[11].rgb = glm::vec3(1.f, 1.f, 0.f);

		color[12].rgb = glm::vec3(1.f, 0.f, 0.f);
		color[13].rgb = glm::vec3(0.f, 1.f, 0.f);
		color[14].rgb = glm::vec3(0.f, 0.f, 1.f);
		color[15].rgb = glm::vec3(1.f, 0.f, 1.f);

		color[16].rgb = glm::vec3(1.f, 0.f, 0.f);
		color[17].rgb = glm::vec3(0.f, 1.f, 0.f);
		color[18].rgb = glm::vec3(0.f, 0.f, 1.f);
		color[19].rgb = glm::vec3(0.f, 1.f, 1.f);

		color[20].rgb = glm::vec3(1.f, 0.f, 0.f);
		color[21].rgb = glm::vec3(0.f, 1.f, 0.f);
		color[22].rgb = glm::vec3(0.f, 0.f, 1.f);
		color[23].rgb = glm::vec3(1.f, 0.f, 1.f);
	}

	//Index
	{
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
	}

	vao->GetVBO<BUFFER_TYPE::Vertex>().SetBuffer(vtx);
	vao->GetVBO<BUFFER_TYPE::Color>().SetBuffer(color);
	vao->GetVBO<BUFFER_TYPE::Index>().SetBuffer(idx);

}
