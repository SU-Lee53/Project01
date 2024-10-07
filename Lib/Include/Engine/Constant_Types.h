#pragma once

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;

	const static uint32 slot = 0;
};

struct TransformData
{
	Matrix matLocal = Matrix::Identity;	// bone local -> model local
	Matrix matWorld = Matrix::Identity; // model local -> world

	const static uint32 slot = 1;
};

struct MaterialData
{
	Color ambient = Color{ 0.f, 0.f, 0.f, 1.f };
	Color diffuse = Color{ 1.f, 1.f, 1.f, 1.f };
	Color specular = Color{ 0.f, 0.f, 0.f, 1.f };
	Color emissive = Color{ 0.f, 0.f, 0.f, 1.f };
};