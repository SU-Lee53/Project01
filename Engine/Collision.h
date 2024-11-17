#pragma once

// Collision check implementation

class SphereCollider;
class PlaneCollider;
class AABBCollider;

class Collision
{
	// NEED TO FIX EVERYTHING
	// COLLISION SHOULD NOT GET SHARED_PTR
	// SHARED_FROM_THIS MAKES CRASH
public:
	static bool CheckCollision(shared_ptr<SphereCollider> sphere1, shared_ptr<SphereCollider> sphere2);
	//static bool CheckCollision(const SphereCollider& sphere1, const SphereCollider& sphere2);
							    				   
	static bool CheckCollision(shared_ptr<SphereCollider> sphere, shared_ptr<PlaneCollider> plane);
							    				   
	static bool CheckCollision(shared_ptr<SphereCollider> sphere, shared_ptr<AABBCollider> aabb);
							    
	static bool CheckCollision(shared_ptr<PlaneCollider> plane1, shared_ptr<PlaneCollider> aabb2);
							    
	static bool CheckCollision(shared_ptr<PlaneCollider> plane, shared_ptr<AABBCollider> aabb);
							    
	static bool CheckCollision(shared_ptr<AABBCollider> aabb1, shared_ptr<AABBCollider> aabb2);


	static Vec3 ClosestPoint(shared_ptr<PlaneCollider> p, shared_ptr<SphereCollider> s);
};

