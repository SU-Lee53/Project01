#include "EnginePch.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(shared_ptr<VAO> vao)
	: _vao(vao)
{
}

Mesh::~Mesh()
{
}
