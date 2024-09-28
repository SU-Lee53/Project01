#include "EnginePch.h"
#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
}

void Mesh::CreateTestGeometry()
{
	Utils::MakeCubeGeometry(_geometry);
}
