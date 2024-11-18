#pragma once
#include "Collider.h"

template <typename C>
class BaseCollider : public Collider
{
	static_assert(IsColliderType<C>);

public:
	BaseCollider(COLLIDER_TYPE ty);
	virtual ~BaseCollider();

public:
	virtual void InitCollider() override
	{
		(static_cast<C*>(this))->UpdateCollider();
	}

	virtual void UpdateCollider() override
	{
		(static_cast<C*>(this))->UpdateCollider();
	}

protected:
	const COLLIDER_TYPE _colliderType;

};

template<typename C>
inline BaseCollider<C>::BaseCollider(COLLIDER_TYPE ty) : _colliderType(ty)
{
}

template<typename C>
inline BaseCollider<C>::~BaseCollider()
{
}
