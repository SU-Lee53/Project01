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
concept OwnerType = IsOwnerType<C>;

class Script
{
	using Owner_Ty = variant<monostate, weak_ptr<GameObject>, weak_ptr<Scene>>;
public:
	Script();
	virtual ~Script();

public:
	virtual void Init();
	virtual void Update();

public:
	template <OwnerType T>
	void SetOwner(T owner);

	template <OwnerType T>
	shared_ptr<T> GetOwner() const;


private:
	Owner_Ty _owner;


public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Script;

};

template<OwnerType T>
inline void Script::SetOwner(T owner)
{
	// TODO : Fill
	if constexpr (is_same_v<T, GameObject>)
	{

	}
	else if constexpr (is_same_v<T, Scene>)
	{

	}
	else
		assert(false);
}

template<OwnerType T>
inline shared_ptr<T> Script::GetOwner() const
{
	// TODO : Fill
	return shared_ptr<T>();
}
