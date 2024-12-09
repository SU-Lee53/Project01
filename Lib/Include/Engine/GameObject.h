#pragma once

#include "Component.h"
#include "Transform.h"
#include "BaseCollider.h"

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

	GameObject(const GameObject& obj) = default;

public:
	void Init();
	void Update();

public:
	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	void AddComponent()
	{
		int32 idx = (int32)(T::ty);
		_components[idx] = make_shared<T>();
		_components[idx]->SetOwner(shared_from_this());
	}

	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	shared_ptr<T> GetComponent()
	{
		static_assert(!std::derived_from<T, BaseCollider>, "To get Collider, Use GetCollider");
		int32 idx = (int32)(T::ty);

		// Every GameObject has Transform
		if (T::ty == COMPONENT_TYPE::Transform and _components[idx] == nullptr) AddComponent<T>();
		return static_pointer_cast<T>(_components[idx]);
	}


	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	void RemoveComponent()
	{
		int32 idx = (int32)(T::ty);
		_components[idx].reset();
	}


	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	bool HasComponent()
	{
		return _components[(int32)(T::ty)] ? true : false;
	}


	/*template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	constexpr shared_ptr<T> GetCollider()
	{
		int32 idx = COMPONENT_TYPE::Collider;

		if constexpr (is_same_v<T, SphereCollider>)
		{

		}
		else if constexpr(is_same_v<T, AABBCollider>)

	}*/



public:
	shared_ptr<Transform> GetTransform() const
	{
		return static_pointer_cast<Transform>(_components[(int)COMPONENT_TYPE::Transform]);
	}

public:
	void AddScript(shared_ptr<Script<GameObject>> script);

public:
	void SetName(const string& name) { _name = name; }
	string GetName() { return _name; }

private:
	array<shared_ptr<Component_Base>, COMPONENT_COUNT> _components;

	// Scripts
	vector<shared_ptr<Script<GameObject>>> _scripts;
	string _name;
};
