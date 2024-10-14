#include "EnginePch.h"
#include "GlobalLight.h"

GlobalLight::GlobalLight()
{
}

GlobalLight::~GlobalLight()
{
}

void GlobalLight::Init_impl()
{
}

void GlobalLight::Update_impl()
{
	PushData();
}

void GlobalLight::SetData(const GlobalLightData& data)
{
	_data = data;
}

void GlobalLight::PushData()
{
	RENDER->SetGlobalLightData(_data);
}
