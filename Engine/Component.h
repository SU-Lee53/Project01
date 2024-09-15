#pragma once


class Component
{
public:
	Component();
	virtual ~Component();

public:
	virtual void Init();
	virtual void Update();

};

