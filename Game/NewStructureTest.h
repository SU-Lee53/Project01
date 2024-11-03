#pragma once
#include "Execute.h"

class NewStructureTest : public Execute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;
	shared_ptr<GameObject> _light;
	shared_ptr<GameObject> _cam;

	shared_ptr<Script<GameObject>> _mouseScript;
	shared_ptr<Script<GameObject>> _modelScript;
	shared_ptr<Script<GameObject>> _lightScript;

};					  

