#pragma once
#include "Manager.h"
#include "Resource_Base.h"

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

private:
	unordered_map<string, shared_ptr<Resource_Base>> _resources;

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Resource;
};

