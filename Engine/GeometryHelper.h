#pragma once

class GeometryHelper
{
public:
	static void CreateSphere(OUT shared_ptr<Geometry<DebugType>> geometry);
	static void CreateCube(OUT shared_ptr<Geometry<DebugType>> geometry);
	static void CreateGrid(OUT shared_ptr<Geometry<DebugType>> geometry);
};

