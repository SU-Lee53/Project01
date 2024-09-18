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
	_world = _local;
}

void Transform::SetPosition(const glm::vec3& pos)
{
	_position = pos;
	_local = glm::translate(IDENTITY, _position);
}

void Transform::SetRotation(const glm::vec3& rot)
{
	_rotation = rot;
	glm::mat4 rotate = glm::rotate(IDENTITY, glm::radians(_rotation.x), AXIS_X);
	rotate = glm::rotate(IDENTITY, glm::radians(_rotation.y), AXIS_Y) * rotate;
	rotate = glm::rotate(IDENTITY, glm::radians(_rotation.z), AXIS_Z) * rotate;
	_local = rotate;
}

void Transform::SetScale(const glm::vec3& scale)
{
	_scale = scale;
	_local = glm::scale(IDENTITY, _scale);
}

void Transform::PushTransform()
{
	RENDER->GetShader()->SetMat4("world", _world);
}
