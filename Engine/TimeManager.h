#pragma once
#include "Manager.h"

class TimeManager : public Manager_Base
{
public:
	TimeManager();
	virtual ~TimeManager();

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	UINT32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	UINT64	_frequency	= 0;
	UINT64	_prevCount	= 0;
	float	_deltaTime	= 0.f;

private:
	UINT32	_frameCount	= 0;
	UINT32	_fps		= 0;
	float	_frameTime	= 0.f;
public:
	constexpr static MANAGER_TYPE ty = MANAGER_TYPE::Time;
};