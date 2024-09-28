#pragma once

class GameObject;
class Transform;
class MeshRenderer;

enum class COMPONENT_TYPE
{
	Transform,
	Camera,
	MeshRenderer,

	End,

	ERROR_TYPE
};

enum
{
	COMPONENT_COUNT = static_cast<int>(COMPONENT_TYPE::End)
};

class Component_Base
{
public:
	Component_Base() {}
	virtual ~Component_Base() {}

public:
	virtual void Init() {}
	virtual void Update() {}

public:
	shared_ptr<GameObject> GetOwner()
	{
		return _owner.lock();
	}

	shared_ptr<Transform> GetTransform()
	{
		return _owner.lock()->GetComponent<Transform>();
	}

protected:
	friend class GameObject;
	void SetOwner(shared_ptr<GameObject> gameObject) { _owner = gameObject; }
	weak_ptr<GameObject> _owner;

};

template <typename T>
class Component : public Component_Base
{
public:
	Component();
	virtual ~Component();

public:
	virtual void Init() override
	{
		(static_cast<T*>(this))->Init_impl();
	}
	virtual void Update() override
	{
		(static_cast<T*>(this))->Update_impl();
	}

protected:
	virtual void Init_impl() {};
	virtual void Update_impl() {};

};

template<typename T>
inline Component<T>::Component()
{
}

template<typename T>
inline Component<T>::~Component()
{
}
