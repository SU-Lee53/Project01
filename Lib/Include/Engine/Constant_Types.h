#pragma once

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;

	const static uint32 slot = 0;
};

struct TransformData
{
	Matrix matWorld = Matrix::Identity;

	const static uint32 slot = 1;
};
