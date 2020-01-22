#pragma once

#include "GameObjects/GameObject.hpp"
#include "Core/CollisionType.hpp"

class CollisionInfo {
public:
	ptr_GameObject collider;
	CollisionType present;
	CollisionType future;

	CollisionInfo(ptr_GameObject collider);
	CollisionInfo(ptr_GameObject collider, CollisionType present, CollisionType future);
};