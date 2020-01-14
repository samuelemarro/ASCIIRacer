#include "Engine/GameEngine.hpp"
#include "GameObjects/PhysicalObject.hpp"
#include "Core/Utilities.hpp"

PhysicalObject::PhysicalObject() : GameObject() {
	//TODO: Deve essere "ignora collisioni"
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, Sprite sprite) : GameObject(rect, layer, sprite) {
	this->collisionLayer = layer;
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, Sprite sprite, Layer collisionLayer, Point2D speed, CollisionMask collisionMask) : PhysicalObject(rect, layer, sprite) {
	this->collisionLayer = collisionLayer;
	this->velocity = speed;
	this->collisionMask = collisionMask;
}


void PhysicalObject::onStart() {}
void PhysicalObject::onUpdate() {}
void PhysicalObject::onCollision(PhysicalObject collider) {}