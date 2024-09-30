#include "pch.h"
#include "Game.h"
#include "Test.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	{
		desc.width = 800;
		desc.height = 600;
		desc.clearColor = Color{ 0.f, 0.f, 0.f, 1.f };
		desc.windowName = L"Billards";
		desc.hInstance = hInstance;
		desc.hWnd = NULL;
		desc.program = make_shared<Test>();
	}

	GAME.Run(desc);

}

