#include "pch.h"
#include "Game.h"
#include "Test.h"
#include "ModelLoader.h"
#include "NewStructureTest.h"
#include "SceneTest.h"
#include "CollisionTest.h"
#include "SceneMaker.h"

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
		desc.program = make_shared<SceneMaker>();

	}

	GAME.Run(desc);
}

