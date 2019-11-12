#include "Engine/GameEngine.hpp"
#include "GameObjects/PhysicalObject.hpp"
#include "Core/Utilities.hpp"

PhysicalObject::PhysicalObject() : GameObject() {
	GameEngine::AddPhysicalObject(*this);
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, Sprite sprite) : GameObject(rect, layer, sprite) {
	GameEngine::AddPhysicalObject(*this);
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, Sprite sprite, Layer collisionLayer, Point2D speed, CollisionMask collisionMask) : PhysicalObject(rect, layer, sprite) {
	this->collisionLayer = collisionLayer;
	this->speed = speed;
	this->collisionMask = collisionMask;
}


void PhysicalObject::onStart() {}
void PhysicalObject::onUpdate() {}
void PhysicalObject::onCollision(PhysicalObject collider) {}