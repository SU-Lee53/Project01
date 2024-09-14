#include "EnginePch.h"
#include "Game.h"
#include "Shader.h"

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

	MANAGER.Init();

	_shader = make_shared<Shader>(L"vs", L"fs");

	_vao = make_shared<VAO>();
	Utils::MakeCubeGeometry(_vao);
	_vao->MakeVAO();

}

static float _temp = 0.0f;

void Game::Update()
{
	MANAGER.Update();

	_desc.clearColor.r = glm::clamp(glm::sin(_temp), 0.0f, 1.0f);
	_desc.clearColor.g = glm::clamp(glm::cos(_temp), 0.0f, 1.0f);
	_desc.clearColor.b = glm::clamp(glm::sin(_temp + 0.5f), 0.0f, 1.0f);

	_temp += 1.0f * TIME->GetDeltaTime();
}

void Game::Render()
{
	glClearColor(_desc.clearColor.r, _desc.clearColor.g, _desc.clearColor.b, _desc.clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	int count = _vao->GetVBO<BUFFER_TYPE::Index>().GetBuffer().size();
	
	glDrawElements(
		GL_TRIANGLES,
		count,
		GL_UNSIGNED_INT,
		0
	);


	glutSwapBuffers();
}
