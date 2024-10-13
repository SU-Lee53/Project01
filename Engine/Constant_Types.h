#pragma once

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
	Matrix matViewinv = Matrix::Identity;

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

struct GlobalLightData
{
	Color ambient = Color{ 0.f, 0.f, 0.f, 1.f };
	Color diffuse = Color{ 1.f, 1.f, 1.f, 1.f };
	Color specular = Color{ 0.f, 0.f, 0.f, 1.f };
	Color emissive = Color{ 0.f, 0.f, 0.f, 1.f };
	Vec3 direction = Vec3{ 1.f,0.f,0.f };
	float padding;
};

struct SpotLightData
{
    Vec4 sPosition;
    // 16

	Vec3 sLightDirection;
    float padding0;
    // 16

	Vec3 sInnerConeDirPositive;
    float padding1;
    // 16

	Vec3 sOuterConeDirPositive;
    float padding2;
    // 16

    Color sAmbient;
    Color sDiffuse;
    Color sSpecular;
    Color sEmissive;
    // 16 * 4
};