#pragma once

class GameObject;

struct GameDesc
{
	int width;
	int height;
	Color clearColor = Color{ 0.f, 0.f, 0.f, 1.f };

	wstring windowName = L"Billards";
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
	shared_ptr<class Execute> program;
};

class Game
{
	DECLARE_SINGLE(Game);

public:
	WPARAM Run(GameDesc& desc);
	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void Update();
	void Render();

	GameDesc& GetDesc() { return _desc; }

private:

private:
	GameDesc _desc;
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _cam;
};

