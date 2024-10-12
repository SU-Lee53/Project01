#include "EnginePch.h"
#include "Game.h"
#include "Mesh.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Execute.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WPARAM Game::Run(GameDesc& desc)
{
	_desc = desc;
	// assert(_desc.app != nullptr);

	MyRegisterClass();

	if (!InitInstance(SW_SHOWNORMAL))
		return FALSE;

	{
		// TODO : Init
		GRAPHICS.Init(_desc.hWnd);
		MANAGER.Init();
		desc.program->Init();
	}

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
		}
	}

	return msg.wParam;
}

#pragma region WinCallbacks

ATOM Game::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _desc.hInstance;
	wcex.hIcon = ::LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _desc.windowName.c_str();
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassExW(&wcex);
}

BOOL Game::InitInstance(int cmdShow)
{
	RECT windowRect = { 0, 0, _desc.width, _desc.height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	_desc.hWnd = CreateWindowW(_desc.windowName.c_str(), _desc.windowName.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, _desc.hInstance, nullptr);

	if (!_desc.hWnd)
		return FALSE;

	::ShowWindow(_desc.hWnd, cmdShow);
	::UpdateWindow(_desc.hWnd);

	return TRUE;
}

LRESULT CALLBACK Game::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_SIZE:
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(handle, message, wParam, lParam);
	}
}

#pragma endregion WinCallbacks

void Game::Update()
{
	MANAGER.Update();

	ShowFps();

	_desc.program->Update();
}

void Game::Render()
{
	GRAPHICS.RenderBegin();
	{
		_desc.program->Render();
		GUI->Render();
	}
	GRAPHICS.RenderEnd();
}

void Game::ShowFps()
{
	uint32 fps = TIME->GetFps();

	WCHAR text[100] = L"";
	wsprintf(text, L"FPS : %d", fps);

	SetWindowText(_desc.hWnd, text);
}
