#include "Core/CollisionInfo.hpp"

CollisionInfo::CollisionInfo(ptr_GameObject collider)
{
	this->collider = collider;
	this->present = CollisionType();
	this->future = CollisionType();
}

CollisionInfo::CollisionInfo(ptr_GameObject collider, CollisionType present, CollisionType future) {
	this->collider = collider;
	this->present = present;
	this->future = future;
}