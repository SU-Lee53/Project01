#pragma once

class Execute
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

