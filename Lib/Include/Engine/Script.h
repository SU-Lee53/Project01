#pragma once

class GameObject;
class Scene;


template <typename C>
concept IsOwnerType = requires (C c)
{
	same_as<C, GameObject> or
		same_as<C, Scene>;
};

template <typename C>
concept ScriptOwnerType = IsOwnerType<C>;

template <ScriptOwnerType T>
class Script
{
	using OwnerTy = T;

public:
	Script();
	virtual ~Script();

public:
	virtual void Init();
	virtual void Update();

public:
	void SetOwner(shared_ptr<T> owner);
	shared_ptr<T> GetOwner() const;


private:
	weak_ptr<T> _owner;

};

template<ScriptOwnerType T>
inline Script<T>::Script()
{
}

template<ScriptOwnerType T>
inline Script<T>::~Script()
{
}

template<ScriptOwnerType T>
inline void Script<T>::Init()
{
}

template<ScriptOwnerType T>
inline void Script<T>::Update()
{
}

template<ScriptOwnerType T>
inline void Script<T>::SetOwner(shared_ptr<T> owner)
{
	_owner = owner;
}

template<ScriptOwnerType T>
inline shared_ptr<T> Script<T>::GetOwner() const
{
	return _owner.lock();
}
