#pragma once
#include "Component.h"

class Collider_Base : public Component<Collider_Base>
{
public:
	Collider_Base();
	virtual ~Collider_Base();

private:

};


template <typename C>
concept IsColliderType = requires(C c)
{
	derived_from<C, Collider_Base>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;
