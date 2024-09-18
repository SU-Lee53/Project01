#pragma once
#include "Component.h"
#include "UBO.h"

enum class PROJECTION_TYPE
{
	Perspective,
	Orthographic
};

class Camera : public Component<Camera>
{
public:
	Camera();
	virtual ~Camera();

public:
	void SetProjectionType(PROJECTION_TYPE ty) { _type = ty; }
	PROJECTION_TYPE GetProjectionType() { return _type; }

public:
	void Update_impl();
	void SetCamera();
	void PushCamera();

public:
	void SetNear(float __near) { _near = __near; }
	void SetFar(float __far) { _far = __far; }
	void SetFovY(float fovy) { _fovy = fovy; }
	void SetWidth(float width) { _width = width; }
	void SetHeight(float height) { _height = height; }

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }

private:
	PROJECTION_TYPE _type = PROJECTION_TYPE::Perspective;
	
	float _near = 1.f;
	float _far = 1000.f;
	float _fovy = 45.f;
	float _width = 800.f;
	float _height = 600.f;

private:
	glm::mat4 _view = IDENTITY;
	glm::mat4 _projection = IDENTITY;

private:
	UBO<Global> _ubo;

public:
	constexpr static COMPONENT_TYPE ty = COMPONENT_TYPE::Camera;
};

