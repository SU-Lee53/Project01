#include "pch.h"
#include "Game.h"

void Game::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(desc.windowPos.x, desc.windowPos.y);
	glutInitWindowSize(desc.width, desc.height);
	glutCreateWindow(desc.windowName.c_str());

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

}

void Game::Update()
{
}

void Game::Render()
{

	glClearColor(desc.clearColor.r, desc.clearColor.g, desc.clearColor.b, desc.clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}
