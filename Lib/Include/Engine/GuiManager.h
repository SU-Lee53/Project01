#pragma once
#include "Manager.h"

class GuiManager : public Manager_Base
{
public:
	GuiManager();
	virtual ~GuiManager();

public:
	virtual void Init() override;
	virtual void Update() override;
	void Render();

public:
	constexpr static  MANAGER_TYPE ty = MANAGER_TYPE::Gui;
};

