#include "EnginePch.h"
#include "Camera.h"
#include "Transform.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update_impl()
{
	SetCamera();
	PushCamera();
}

void Camera::SetCamera()
{
	Vec3 eye = GetTransform()->
}

void Camera::PushCamera()
{
}
