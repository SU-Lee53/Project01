#pragma once

enum class RESOURCE_TYPE
{
	Base = -1,

	Mesh = 0,
	Texture,

	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<uint8>(RESOURCE_TYPE::End) - 1
};

class Resource_Base : public enable_shared_from_this<Resource_Base>
{
public:
	Resource_Base();
	virtual ~Resource_Base();

	void SetName(const wstring& name) { _name = name; }
	void SetPath(const wstring& path) { _path = path; }
	
	wstring GetName() { return _name; }
	wstring GetPath() { return _path; }

public:
	virtual void Load(const wstring& path);
	virtual void Save(const wstring& path);

private:
	wstring _name;
	wstring _path;
	uint32 _id;

public:
	using Ty = Resource_Base;
};

