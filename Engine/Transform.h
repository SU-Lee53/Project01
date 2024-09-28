#pragma once
#include "Component.h"


class Transform : public Component<Transform>
{
public:
	Transform();
	virtual ~Transform();
	
public:
	void Update_impl();
	void UpdateMatrix();

	void SetPosition(const Vec3& pos);
	void SetRotation(const Vec3& rot);
	void SetScale(const Vec3& scale);
	
	Vec3 GetPosition() { return _position; }
	Vec3 GetRotation() { return _rotation; }
	Vec3 GetScale() { return _scale; }

	Matrix GetLocal() { return _local; }
	Matrix GetWorld() { return _world; }

public:
	void PushTransform();

private:
	Vec3 _position = { 0.f, 0.f, 0.f };
	Vec3 _rotation = { 0.f, 0.f, 0.f };
	Vec3 _scale = { 1.f, 1.f, 1.f };

	Matrix _local = Matrix::Identity;
	Matrix _world = Matrix::Identity;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Transform;
};

