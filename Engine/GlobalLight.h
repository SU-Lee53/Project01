#pragma once
#include "Light_Base.h"

class GlobalLight : public Light_Base
{
public:
	GlobalLight();
	virtual ~GlobalLight();

public:
	void Init_impl();
	void Update_impl();

public:
	void SetData(const GlobalLightData& data);
	GlobalLightData& GetData() { return _data; }

	void PushData();

private:
	GlobalLightData _data;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::GlobalLight;
};

