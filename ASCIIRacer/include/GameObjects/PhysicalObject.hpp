#pragma once

#include "GameObject.hpp"
#include "Core/Typedefs.hpp"

class PhysicalObject : public GameObject
{
public:
	Layer collisionLayer;
	CollisionMask collisionMask;
	Point2D velocity;
	bool immovable;

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual void onCollision(PhysicalObject* collider);

	PhysicalObject(Rect rect, Layer layer, Sprite sprite);
	PhysicalObject(Rect rect, Layer layer, Sprite sprite, Layer collisionLayer, Point2D speed, CollisionMask collisionMask, bool immovable);
	PhysicalObject();
};

typedef PhysicalObject* ptr_PhysicalObject;