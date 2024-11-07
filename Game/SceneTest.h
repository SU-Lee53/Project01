#pragma once
#include "Execute.h"

class SceneTest : public Execute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};

