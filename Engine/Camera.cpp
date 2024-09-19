#include "EnginePch.h"
#include "Camera.h"
#include "UBO.h"

Camera::Camera()
{
	_ubo = make_shared<UBO<Global>>();
	_ubo->Create("Global");
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
	glm::vec3 forward = glm::vec3{ transform[0][2], transform[1][2], transform[2][2] };

	glm::vec3 eye = GetOwner()->GetComponent<Transform>()->GetPosition();
	glm::vec3 at = glm::normalize(eye + forward);
	glm::vec3 up = glm::vec3{ transform[0][1], transform[1][1], transform[2][1] };

	_view = glm::lookAt(eye, at, up);
}

void Camera::PushCamera()
{
	//	TODO : make UBO and push
	_ubo->PushData(_view);
	_ubo->PushData(_projection);

	//	RENDER->GetShader()->SetMat4("view", _view);
	//	RENDER->GetShader()->SetMat4("projection", _projection);

}
