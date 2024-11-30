#include "EnginePch.h"
#include "Camera.h"
#include "Transform.h"
#include "Constant_Types.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update_impl()
{
	SetCamera();
}

void Camera::SetCamera()
{
	Vec3 eye = GetTransform()->GetPosition();
	Vec3 at = eye + GetTransform()->GetLook();
	Vec3 up = GetTransform()->GetUp();

	_view = XMMatrixLookAtLH(eye, at, up);

	if(_type == PROJECTION_TYPE::Perspective)
	{
		_projection = XMMatrixPerspectiveFovLH
		(
			_fovy,
			_width / _height,
			_near,
			_far
		);
	}
	else
	{
		_projection = XMMatrixOrthographicLH
		(
			_width,
			_height,
			_near,
			_far
		);
	}
}

void Camera::PushCamera()
{
	RENDER->SetCameraData(CameraData{_view, _projection, _view.Invert()});
}

CameraData Camera::GetCameraData()
{
	return CameraData{ _view, _projection, _view.Invert() };
}
