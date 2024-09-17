#pragma once


enum class COMPONENT_TYPE
{
	Camera,
	Transform,

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

private:
	virtual void Init_impl() {};
	virtual void Update_impl() {};

private:
	friend class GameObject;
	void SetOwner(shared_ptr<GameObject> gameObject) { _owner = gameObject; }
	shared_ptr<class GameObject> GetOwner();

private:
	weak_ptr<class GameObject> _owner;

};

template<typename T>
inline Component<T>::Component()
{
}

template<typename T>
inline Component<T>::~Component()
{
}

template<typename T>
inline shared_ptr<class GameObject> Component<T>::GetOwner()
{
	return _owner.lock();
}
