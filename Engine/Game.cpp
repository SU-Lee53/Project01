#include "EnginePch.h"
#include "Game.h"

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

}

void Game::Update()
{
}

void Game::Render()
{
	glClearColor(_desc.clearColor.r, _desc.clearColor.g, _desc.clearColor.b, _desc.clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	MANAGER.GetManager<ManagerType::Time>();
	glutSwapBuffers();
}
