#include "pch.h"

Game game{};

void Render()
{
	game.Render();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv)
{
	GameDesc& desc = game.GetDesc();
	{
		desc.width = 800;
		desc.height = 600;
		desc.windowName = "Billards";
		desc.windowPos = { 100.f, 100.f };
		desc.clearColor = { 0.f, 0.f, 0.f };
	}

	game.Init(argc, argv);

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);

	while (true)
	{
		game.Update();

		glutPostRedisplay();
		glutMainLoopEvent();
	}

}

