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
	~Component_Base() {}
};

template <typename T>
class Component : public Component_Base
{
public:
	Component();
	virtual ~Component();

public:
	void Init()
	{
		(static_cast<T*>(this))->Init_impl();
	}
	void Update()
	{
		(static_cast<T*>(this))->Update_impl();
	}

private:
	virtual void Init_impl() {};
	virtual void Update_impl() {};

private:
	friend class GameObject;
	void SetOwner(shared_ptr<GameObject> gameObject) { _owner = gameObject; }

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
