#pragma once

// Collision check implementation

class SphereCollider;
class PlaneCollider;
class AABBCollider;

class Collision
{
public:
	static bool CheckCollision(const SphereCollider& sphere1, const SphereCollider& sphere2);
							    				   
	static bool CheckCollision(const SphereCollider& sphere, const PlaneCollider& plane);
							    				   
	static bool CheckCollision(const SphereCollider& sphere, const AABBCollider& aabb);
							    
	static bool CheckCollision(const PlaneCollider& plane1, const PlaneCollider& aabb2);
							    
	static bool CheckCollision(const PlaneCollider& plane, const AABBCollider& aabb);
							    
	static bool CheckCollision(const AABBCollider& aabb1, const AABBCollider& aabb2);


	static Vec3 ClosestPoint(const PlaneCollider& p, const SphereCollider s);
};

