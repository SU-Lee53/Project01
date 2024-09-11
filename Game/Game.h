#pragma once

struct GameDesc
{
	int width;
	int height;
	Pos2D windowPos;
	string windowName;
	RGB clearColor;
};

class Game
{
public:

	void Init(int argc, char** argv);
	void Update();
	void Render();

	GameDesc& GetDesc() { return desc; }

private:

private:
	GameDesc desc;

};

