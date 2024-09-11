#include "pch.h"


int main(int argc, char** argv)
{
	shared_ptr<Game> game = make_shared<Game>();

	GameDesc& desc = game->GetDesc();
	{
		desc.width = 800;
		desc.height = 600;
		desc.windowName = "Billards";
		desc.windowPos = { 100.f, 100.f };
		desc.clearColor = { 0.f, 1.f, 0.f };
	}

	game->Init(argc, argv);

	while (true)
	{
		game->Update();
		game->Render();
	}

}