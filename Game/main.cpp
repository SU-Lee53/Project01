#include "pch.h"

Game game{};

void Render()
{
	glClearColor(game.GetDesc().clearColor.r, game.GetDesc().clearColor.g, game.GetDesc().clearColor.b, game.GetDesc().clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.Render();

	glutSwapBuffers();
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

	while (true)
	{
		game.Update();

		glutPostRedisplay();
		glutMainLoopEvent();
	}

}