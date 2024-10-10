#pragma once
#include "Collider_Base.h"


class SphereCollider : public Collider_Base
{
};



static_assert(derived_from<SphereCollider, Collider_Base>);