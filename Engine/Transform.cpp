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
	_local = glm::rotate(IDENTITY, glm::radians(_rotation.x), AXIS_X);
	_local = glm::rotate(IDENTITY, glm::radians(_rotation.y), AXIS_Y);
	_local = glm::rotate(IDENTITY, glm::radians(_rotation.z), AXIS_Z);
}

void Transform::SetScale(const glm::vec3& scale)
{
	_scale = scale;
	_local = glm::scale(IDENTITY, _scale);
}
