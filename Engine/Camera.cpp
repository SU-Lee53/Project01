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
	SetCamera();
	PushCamera();
}

void Camera::SetCamera()
{
	if (_type == PROJECTION_TYPE::Perspective)
		_projection = glm::perspective(_fovy, _width / _height, _near, _far);
	else
		_projection = glm::ortho(-5.f, 5.f, -5.f, 5.f, -5.f, 5.f);
	
	glm::mat4 transform = GetOwner()->GetComponent<Transform>()->GetWorld();
	glm::vec3 forward = glm::vec3{ transform[1][3], transform[2][3], transform[3][3] };

	glm::vec3 eye = GetOwner()->GetComponent<Transform>()->GetPosition();
	glm::vec3 at = eye + forward;
	glm::vec3 up = glm::vec3{ transform[1][2], transform[2][2], transform[3][2] };

	_view = glm::lookAt(eye, at, up);
}

void Camera::PushCamera()
{
	Global globalData{ _view, _projection };

	// TODO : make UBO and push
	//_ubo.BindUniformBlock("Global");
	//_ubo.Create();
	//_ubo.SetSubData(globalData);

	RENDER->GetShader()->SetMat4("view", _view);

	RENDER->GetShader()->SetMat4("projection", _projection);
}
