#include "EnginePch.h"
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update_impl()
{
}

void Camera::SetCamera()
{
	if (_type == PROJECTION_TYPE::Perspective)
		_projection = glm::perspective(_fovy, _width / _height, _near, _far);
	else
		_projection = glm::ortho(-5.f, 5.f, -5.f, 5.f, -5.f, 5.f);
}

void Camera::PushCamera()
{
	Global globalData{ _view, _projection };

	unsigned int loc = RENDER->GetShader()->GetUniformBlockLocation("Global");
	glUniformBlockBinding(RENDER->GetShader()->GetID(), loc, 0);

	// TODO : make UBO and push
}
