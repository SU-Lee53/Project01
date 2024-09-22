#pragma once

class RasterizerState;
class BlendState;

class Renderer
{
public:
	Renderer();
	~Renderer();


private:

private:
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<BlendState> _blendState;

};

