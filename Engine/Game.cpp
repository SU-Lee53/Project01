#include "EnginePch.h"
#include "Game.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshRenderer.h"

void Game::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(_desc.windowPos.x, _desc.windowPos.y);
	glutInitWindowSize(_desc.width, _desc.height);
	glutCreateWindow(_desc.windowName.c_str());

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to init GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initialized" << std::endl;
	}

	_shader = make_shared<Shader>(L"vs", L"fs");

	MANAGER.Init(_shader);

	{
		_camera = make_shared<GameObject>();
		_camera->AddComponent<Camera>();
		_camera->GetComponent<Transform>()->SetPosition(glm::vec3{ 0.0f, 0.0f, 3.0f });
	}

	{
		_vao = make_shared<VAO>();
		Utils::MakeCubeGeometry(_vao);
		_vao->Create();
		shared_ptr<Mesh> m = make_shared<Mesh>(_vao);

		_obj = make_shared<GameObject>();
		_obj->AddComponent<MeshRenderer>();
		_obj->GetComponent<MeshRenderer>()->SetMesh(m);
		_obj->GetComponent<Transform>()->SetPosition(glm::vec3{ 0.0f, 0.0f, 0.0f });

	}

}

static float _temp = 0.0f;
static glm::vec3 rotation{ 45.f,0.f,0.f };

void Game::Update()
{
	MANAGER.Update();
	{
		_desc.clearColor.r = glm::clamp(glm::sin(_temp), 0.0f, 1.0f);
		_desc.clearColor.g = glm::clamp(glm::cos(_temp), 0.0f, 1.0f);
		_desc.clearColor.b = glm::clamp(glm::sin(_temp + 0.5f), 0.0f, 1.0f);

		rotation.y += 10.0f * TIME->GetDeltaTime();
		_obj->GetComponent<Transform>()->SetRotation(rotation);

		_temp += 1.0f * TIME->GetDeltaTime();
	}

	_obj->Update();

}

void Game::Render()
{
	// Render begin
	glClearColor(_desc.clearColor.r, _desc.clearColor.g, _desc.clearColor.b, _desc.clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);

	// Whole render part
	{
		RENDER->Render(_obj);
	}

	// Render end
	glutSwapBuffers();
}
