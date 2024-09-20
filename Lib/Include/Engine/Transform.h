#pragma once
#include "Component.h"


class Transform : public Component<Transform>
{
public:
	Transform();
	virtual ~Transform();
	
//public:
//	void Update_impl();
//	void UpdateMatrix();
//
//	void SetPosition(const glm::vec3& pos);
//	void SetRotation(const glm::vec3& rot);
//	void SetScale(const glm::vec3& scale);
//	
//	glm::vec3 GetPosition() { return _position; }
//	glm::vec3 GetRotation() { return _rotation; }
//	glm::vec3 GetScale() { return _scale; }
//
//	glm::mat4 GetLocal() { return _local; }
//	glm::mat4 GetWorld() { return _world; }
//
//public:
//	void PushTransform();
//
//private:
//	glm::vec3 _position = { 0.f, 0.f, 0.f };
//	glm::vec3 _rotation = { 0.f, 0.f, 0.f };
//	glm::vec3 _scale = { 1.f, 1.f, 1.f };
//
//	glm::mat4 _local = IDENTITY;
//	glm::mat4 _world = IDENTITY;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Transform;
};

