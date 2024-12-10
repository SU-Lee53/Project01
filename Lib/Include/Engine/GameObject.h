#pragma once

#include "Component.h"

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
		//static_assert(!std::derived_from<T, BaseCollider>, "To get Collider, Use GetCollider");
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

	template <ColliderType C>
	shared_ptr<C> GetCollider()
	{
		auto p = static_pointer_cast<BaseCollider>(_components[(int32)(COMPONENT_TYPE::Collider)]);
		COLLIDER_TYPE ty = p->GetColliderType();

		if constexpr (is_same_v<C, SphereCollider>)
		{
			if (ty == COLLIDER_TYPE::Sphere) return static_pointer_cast<SphereCollider>(p);
			else return nullptr;
		}
		else if constexpr (is_same_v<C, AABBCollider>)
		{
			if (ty == COLLIDER_TYPE::AABB) return static_pointer_cast<AABBCollider>(p);
			else return nullptr;
		}
		else if constexpr (is_same_v<C, PlaneCollider>)
		{
			if (ty == COLLIDER_TYPE::Plane) return static_pointer_cast<PlaneCollider>(p);
			else return nullptr;
		}

		assert(false);
		return nullptr;
	}


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
