#pragma once
#include "Component.h"

enum class PROJECTION_TYPE
{
	Perspective,
	Orthographic
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

public:
	void SetProjectionType(PROJECTION_TYPE ty) { _type = ty; }
	PROJECTION_TYPE GetProjectionType() { return _type; }

public:
	virtual void Update();

	void SetCamera();

public:
	void SetNear(float __near) { _near = __near; }
	void SetFar(float __far) { _far = __far; }
	void SetFov(float fov) { _fov = fov; }
	void SetWidth(float width) { _width = width; }
	void SetHeight(float height) { _height = height; }

	float GetWidth() { return _width; }
	float GetHeight() { return _height; }

private:
	PROJECTION_TYPE _type = PROJECTION_TYPE::Perspective;
	float _near;
	float _far;
	float _fov;
	float _width;
	float _height;

private:
	glm::mat4 _view;
	glm::mat4 _projection;
};

