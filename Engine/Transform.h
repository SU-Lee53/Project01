#pragma once
#include "Component.h"


class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	glm::quat q;

private:
	glm::mat4 _local = glm::mat4(1.0f);
	glm::mat4 _world = glm::mat4(1.0f);
};

