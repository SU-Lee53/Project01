#pragma once
#include "Component_Base.h"

// TODO : Make Base
// TODO2 : Make BoundingSphere, Plane

class Collider_Base : public Component<Collider_Base>
{
public:



private:

};

template <typename C>
concept IsColliderType = requires(C c)
{
	derived_from<C, Collider_Base>;
};

template <typename C>
concept ColliderType = IsColliderType<C>;
