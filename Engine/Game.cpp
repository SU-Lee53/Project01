#include "EnginePch.h"
#include "Game.h"
#include "Mesh.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"

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

		{
			_obj = make_shared<GameObject>();
			_obj->AddComponent<Transform>();
			_obj->AddComponent<MeshRenderer>();
			_obj->Init();


			auto mesh = make_shared<Mesh>();
			mesh->CreateTestGeometry();
			_obj->GetComponent<MeshRenderer>()->SetMesh(mesh);
		}

		{
			_cam = make_shared<GameObject>();
			_cam->AddComponent<Transform>();
			_cam->AddComponent<Camera>();
			_cam->Init();

			_cam->GetComponent<Transform>()->SetPosition(Vec3{ 0.0f, 0.0f, -5.0f });
		}

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

float temp = 0.0f;

void Game::Update()
{
	MANAGER.Update();

	{
		_obj->GetComponent<Transform>()->SetRotation(Vec3{ 45.f, temp, 45.f });
		temp += 50.f * DELTA_TIME;
	}


	_obj->Update();
	_cam->Update();
}

void Game::Render()
{
	GRAPHICS.RenderBegin();
	{
		RENDER->Render();
	}
	GRAPHICS.RenderEnd();
}
