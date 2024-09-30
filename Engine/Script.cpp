#include "EnginePch.h"
#include "Script.h"

Script::Script()
{
}

Script::~Script()
{
}

void Script::Init()
{
}

void Script::Update()
{
}

shared_ptr<GameObject> Script::GetOwner() const
{
	return _owner.lock();
}
