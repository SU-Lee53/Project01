#include "pch.h"
Game game{};

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

	game = Game();
	game.Run(desc);

	//game.Init(argc, argv);
	//
	//glutDisplayFunc(Render);
	//glutReshapeFunc(Reshape);
	//
	//while (true)
	//{
	//	game.Update();
	//
	//	glutPostRedisplay();
	//	glutMainLoopEvent();
	//}

}

