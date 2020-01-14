#include "Engine/GameEngine.hpp"
#include "GameObjects/PhysicalObject.hpp"
#include "Core/Utilities.hpp"

PhysicalObject::PhysicalObject() : GameObject() {
	this->immovable = false;
	this->velocity = Point2D(0, 0);
	this->collisionLayer = Layer::Content;
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, Sprite sprite) : GameObject(rect, layer, sprite) {
	this->collisionLayer = layer;
	this->immovable = false;
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, Sprite sprite, Layer collisionLayer, Point2D speed, CollisionMask collisionMask, bool immovable) : PhysicalObject(rect, layer, sprite) {
	this->collisionLayer = collisionLayer;
	this->velocity = speed;
	this->collisionMask = collisionMask;
	this->immovable = immovable;
}


void PhysicalObject::onStart() {}
void PhysicalObject::onUpdate() {}
void PhysicalObject::onCollision(ptr_PhysicalObject collider) {}