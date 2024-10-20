#pragma once
#include "Manager.h"
#include "Resource_Base.h"
#include "Shader_Base.h"

class ResourceManager : public Manager_Base
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	void Add(const string& name, shared_ptr<Resource_Base> res);

	template <typename T>
	shared_ptr<T> Get(const string& name)
	{
		auto it = _resources.find(name);
		if (it != _resources.end())
		{
			return static_pointer_cast<T>(it->second);
		}
		
		assert(false);
	}

public:
	void AddVertexShader(shared_ptr<VertexShader> shader);
	shared_ptr<VertexShader> GetVertexShader(const string& name);
	
	void AddPixelShader(shared_ptr<PixelShader> shader);
	shared_ptr<PixelShader> GetPixelShader(const string& name);

	unordered_set<shared_ptr<VertexShader>> GetVertexShaderSet() const { return _vsMap; }
	unordered_set<shared_ptr<PixelShader>> GetPixelShaderSet() const { return _psMap; }

private:
	unordered_map<string, shared_ptr<Resource_Base>> _resources;

	unordered_set<shared_ptr<VertexShader>> _vsMap;
	unordered_set<shared_ptr<PixelShader>> _psMap;

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Resource;
};

