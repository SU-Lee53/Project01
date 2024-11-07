#include "pch.h"
#include "Game.h"
#include "Test.h"
#include "ModelLoader.h"
#include "NewStructureTest.h"
#include "SceneTest.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	{
		desc.width = 1280;
		desc.height = 720;
		desc.clearColor = Color{ 0.f, 0.f, 0.f, 1.f };
		desc.windowName = L"Billards";
		desc.hInstance = hInstance;
		desc.hWnd = NULL;
		desc.program = make_shared<SceneTest>();

	}

	GAME.Run(desc);
}

