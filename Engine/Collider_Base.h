#pragma once
#include "Component_Base.h"

// TODO : Make Base
// TODO2 : Make BoundingSphere, Plane

template <typename C>
concept IsColliderType = requires(C c)
{

};


class Collider_Base : public Component<Collider_Base>
{
public:



private:

};

