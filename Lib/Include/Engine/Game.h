#pragma once


struct GameDesc
{
	int width;
	int height;
	Pos2D windowPos;
	string windowName;
	Color clearColor;
};

class Game
{
public:

	void Init(int argc, char** argv);
	void Update();
	void Render();

	GameDesc& GetDesc() { return _desc; }

private:

private:
	GameDesc _desc;
	shared_ptr<class Shader> _shader;
	//shared_ptr<class VAO> _vao;

	unsigned int _vao;
	unsigned int _vbo[2];

	float vertex[3][3] =
	{
		{-0.5f,	-0.5f,	0.0f},
		{0.5f,	-0.5f,	0.0f},
		{0.0f,	0.5f,	0.0f}
	};

	float color[3][3] =
	{
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f}
	};

	
};

