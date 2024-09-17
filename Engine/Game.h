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
	shared_ptr<class VAO> _vao;
	shared_ptr<class GameObject> _obj;

};

