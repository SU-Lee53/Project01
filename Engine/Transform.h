#pragma once
#include "Component.h"

class Transform : public Component<Transform>
{
public:
	Transform();
	virtual ~Transform();
	
public:
	void Init_impl();
	void Update_impl();
	void UpdateMatrix();

	void SetPosition(const Vec3& pos);
	void SetRotation(const Vec3& rot);
	void SetScale(const Vec3& scale);
	
	Vec3 GetPosition() { return _position; }
	Vec3 GetRotation() { return _rotation; }
	Quaternion GetQuaternion() { return _quaternion; }
	Vec3 GetScale() { return _scale; }
	
	void SetLocalPosition(const Vec3& pos);
	void SetLocalRotation(const Vec3& rot);
	void SetLocalScale(const Vec3& scale);
	
	Vec3 GetLocalPosition() { return _localPosition; }
	Vec3 GetLocalRotation() { return _localRotation; }
	Quaternion GetLocalQuaternion() { return _localQuaternion; }
	Vec3 GetLocalScale() { return _localScale; }

	Vec3 GetLook() { return _world.Backward(); }
	Vec3 GetUp() { return _world.Up(); }
	Vec3 GetRight() { return _world.Right(); }

	Matrix GetLocal() { return _local; }
	Matrix GetWorld() { return _world; }

public:
	void PushTransform();

private:
	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	Vec3 _localRotation = { 0.f, 0.f, 0.f };
	Quaternion _localQuaternion = { 0.f,0.f,0.f,0.f };
	Vec3 _localScale = { 1.f, 1.f, 1.f };
	
	Vec3 _position = { 0.f, 0.f, 0.f };
	Vec3 _rotation = { 0.f, 0.f, 0.f };
	Quaternion _quaternion = { 0.f,0.f,0.f,0.f };
	Vec3 _scale = { 1.f, 1.f, 1.f };


	Matrix _local = Matrix::Identity;
	Matrix _world = Matrix::Identity;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Transform;
};

