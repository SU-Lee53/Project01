#include "pch.h"
#include "ModelLoader.h"
#include "Converter.h"

void ModelLoader::Init()
{
	_converter = make_shared<Converter>();

	_converter->LoadAssetFile();
}

void ModelLoader::Update()
{
}

void ModelLoader::Render()
{
}
