#pragma once

#include "Component.h"
#include "Transform.h"
#include "Collider.h"

class SphereCollider;
class PlaneCollider;
class AABBCollider;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

public:
	void Init();
	void Update();

public:
	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	void AddComponent()
	{
		int idx = (int)(T::ty);
		_components[idx] = make_shared<T>();
		_components[idx]->SetOwner(shared_from_this());
	}

	template <typename T,
		typename = typename enable_if<is_base_of_v<Component_Base, T>>::type>
	shared_ptr<T> GetComponent()
	{
		int idx = (int)(T::ty);

		// Every GameObject has Transform
		if (T::ty == COMPONENT_TYPE::Transform and _components[idx] == nullptr) AddComponent<T>();
		return static_pointer_cast<T>(_components[idx]);
	}

	template <ColliderType T>
	shared_ptr<T> GetCollider()
	{
		if (_components[(int)COMPONENT_TYPE::Collider] == nullptr)
			assert(false);

		// WE NEED TO FIND THE WAY TO RETURN ORIGINAL COLLIDER TYPE!!!
		if (T::_colliderType == COLLIDER_TYPE::Sphere)
			return static_pointer_cast<SphereCollider>(_components[(int)COMPONENT_TYPE::Collider]);
		else if (T::_colliderType == COLLIDER_TYPE::Plane)
			return static_pointer_cast<PlaneCollider>(_components[(int)COMPONENT_TYPE::Collider]);
		else if (T::_colliderType == COLLIDER_TYPE::AABB)
			return static_pointer_cast<AABBCollider>(_components[(int)COMPONENT_TYPE::Collider]);

	}

	shared_ptr<Transform> GetTransform() const
	{
		return static_pointer_cast<Transform>(_components[(int)COMPONENT_TYPE::Transform]);
	}

public:
	void AddScript(shared_ptr<Script<GameObject>> script);

private:
	array<shared_ptr<Component_Base>, COMPONENT_COUNT> _components;

	// Scripts
	vector<shared_ptr<Script<GameObject>>> _scripts;
};
