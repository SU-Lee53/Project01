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

void Utils::MakeCubeGeometry(OUT shared_ptr<VAO>& vao)
{
	//auto vertex = vao.GetVBO<BUFFER_TYPE::Vertex>();
	//auto index = vao.GetVBO<BUFFER_TYPE::Index>();
	//auto color = vao.GetVBO<BUFFER_TYPE::Color>();
	
	vector<glm::vec3> vtx;
	vtx.resize(4);

	vector<glm::vec3> color;
	color.resize(4);

	vtx[0] = glm::vec3(-0.5f, -0.5f, 0.f);
	color[0] = glm::vec3(1.0f, 0.0f, 0.0f);

	vtx[1] = glm::vec3(-0.5f, 0.5f, 0.f);
	color[1] = glm::vec3(0.0f, 1.0f, 0.0f);

	vtx[2] = glm::vec3(0.5f, -0.5f, 0.f);
	color[2] = glm::vec3(0.0f, 0.0f, 1.0f);

	vtx[3] = glm::vec3(0.5f, 0.5f, 0.f);
	color[3] = glm::vec3(1.0f, 0.0f, 1.0f);

	vector<unsigned int> idx = { 2, 1, 0, 2, 3, 1 };

	vector<float> v;
	vector<float> c;
	
	for (auto& vt : vtx)
	{
		v.push_back(vt.x);
		v.push_back(vt.y);
		v.push_back(vt.z);
	}
	
	for (auto& col : color)
	{
		c.push_back(col.x);
		c.push_back(col.y);
		c.push_back(col.z);
	}

	vao->GetVBO<BUFFER_TYPE::Vertex>().SetBuffer(v);
	vao->GetVBO<BUFFER_TYPE::Color>().SetBuffer(c);
	vao->GetVBO<BUFFER_TYPE::Index>().SetBuffer(idx);

}
