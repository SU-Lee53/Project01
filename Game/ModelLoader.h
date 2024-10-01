#pragma once
#include "Execute.h"

class Converter;

class ModelLoader : public Execute
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


private:
	shared_ptr<Converter> _converter;

};

