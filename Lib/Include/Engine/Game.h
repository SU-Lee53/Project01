#pragma once


struct GameDesc
{
	int width;
	int height;
	string windowName;
	Color clearColor;

	wstring appName = L"Billards";
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
};

class Game
{
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
	shared_ptr<class Shader> _shader;
	shared_ptr<class VAO> _vao;
	shared_ptr<class GameObject> _obj;
	shared_ptr<class GameObject> _camera;

};

