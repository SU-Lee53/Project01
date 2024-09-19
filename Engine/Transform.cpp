#include "EnginePch.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
	
}

void Transform::Update_impl()
{
	UpdateMatrix();
	_world = _local;
}

void Transform::UpdateMatrix()
{
	_local = glm::translate(IDENTITY, _position);

	glm::mat4 rotate = glm::rotate(IDENTITY, glm::radians(_rotation.x), AXIS_X);
	rotate = glm::rotate(IDENTITY, glm::radians(_rotation.y), AXIS_Y) * rotate;
	rotate = glm::rotate(IDENTITY, glm::radians(_rotation.z), AXIS_Z) * rotate;
	_local = rotate * _local;

	_local = glm::scale(IDENTITY, _scale) * _local;
}

void Transform::SetPosition(const glm::vec3& pos)
{
	_position = pos;
}

void Transform::SetRotation(const glm::vec3& rot)
{
	_rotation = rot;
}

void Transform::SetScale(const glm::vec3& scale)
{
	_scale = scale;
}

void Transform::PushTransform()
{
	RENDER->GetShader()->SetMat4("world", _world);
}
