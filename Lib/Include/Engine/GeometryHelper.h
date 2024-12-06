#pragma once
class GeometryHelper

{
	static void CreateSphere(Vec3 center, float radius, OUT shared_ptr<Geometry<DebugType>> geometry);
	static void CreateCube(Vec3 center, float extents, OUT shared_ptr<Geometry<DebugType>> geometry);
	static void CreateGrid(int32 sizeX, int32 sizeY, OUT shared_ptr<Geometry<DebugType>> geometry);
};

