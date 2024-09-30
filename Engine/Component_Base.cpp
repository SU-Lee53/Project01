#include "EnginePch.h"
#include "Component_Base.h"
#include "GameObject.h"

shared_ptr<GameObject> Component_Base::GetOwner()
{
	return _owner.lock();;
}

shared_ptr<Transform> Component_Base::GetTransform()
{
	return _owner.lock()->GetTransform();
}

void Component_Base::SetOwner(shared_ptr<GameObject> gameObject)
{ 
	_owner = gameObject; 
}
