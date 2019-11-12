#include "GameObjects/PhysicalObject.hpp"
#include "Core/Utilities.hpp"

PhysicalObject::PhysicalObject(Rect rect, Layer layer, char* sprite, Layer collisionLayer, Point2D speed, bool* collisionMask) : GameObject(rect, layer, sprite), collisionLayer(collisionLayer), speed(speed) {
	if (collisionMask == NULL) {
		this->collisionMask = new bool[rect.size.length()];
		Utilities::fill2D(this->collisionMask, rect.size, true);
	}
	else {
		this->collisionMask = collisionMask;
	}
}

PhysicalObject::PhysicalObject(Rect rect, Layer layer, char* sprite) : PhysicalObject(rect, layer, sprite, layer) {
}

void PhysicalObject::onStart() {}
void PhysicalObject::onUpdate() {}
void PhysicalObject::onCollision(PhysicalObject collider) {}