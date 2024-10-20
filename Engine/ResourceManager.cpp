#include "EnginePch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Add(const string& name, shared_ptr<Resource_Base> res)
{
	_resources.insert(make_pair(name, res));
}

void ResourceManager::AddVertexShader(shared_ptr<VertexShader> shader)
{
	_vsMap.insert(shader);
}

shared_ptr<VertexShader> ResourceManager::GetVertexShader(const string& name)
{
	auto it = find_if(_vsMap.begin(), _vsMap.end(),
		[name](shared_ptr<VertexShader> vs)->bool
		{
			if (vs->GetName() == name) return true;
			return false;
		}
	);

	if (it == _vsMap.end())
	{
		assert(false, "Failed to find shader");
		return nullptr;
	}

	return *it;
}

void ResourceManager::AddPixelShader(shared_ptr<PixelShader> shader)
{
	_psMap.insert(shader);
}

shared_ptr<PixelShader> ResourceManager::GetPixelShader(const string& name)
{
	auto it = find_if(_psMap.begin(), _psMap.end(),
		[name](shared_ptr<PixelShader> ps)->bool
		{
			if (ps->GetName() == name) return true;
			return false;
		}
	);

	if (it == _psMap.end())
	{
		assert(false, "Failed to find shader");
		return nullptr;
	}

	return *it;
}
