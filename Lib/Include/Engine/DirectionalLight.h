#pragma once
#include "Light_Base.h"

class DirectionalLight : public Light_Base
{
public:
	DirectionalLight();
	virtual ~DirectionalLight();

public:
	void Init_impl();
	void Update_impl();

public:
	void SetData(const GlobalLightData& data);
	GlobalLightData& GetData() { return _data; }

	void PushData();

private:
	GlobalLightData _data;
	shared_ptr<ConstantBuffer<GlobalLightData>> _buffer;


public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::DirectionalLight;
};

