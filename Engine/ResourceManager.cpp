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
	_resources.insert(make_tuple(name, res));
}
