#pragma once

#include "GameObject.hpp"
#include "Core/Typedefs.hpp"

class PhysicalObject : public GameObject
{
public:
	Layer collisionLayer;
	CollisionMask collisionMask;

	//Rimuovere speed e rinominare Point2D->Position?
	Point2D speed;

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual void onCollision(PhysicalObject collider);

	PhysicalObject(Rect rect, Layer layer, Sprite sprite);
	PhysicalObject(Rect rect, Layer layer, Sprite sprite, Layer collisionLayer, Point2D speed, CollisionMask collisionMask);
	PhysicalObject();
};

typedef PhysicalObject* ptr_PhysicalObject;