#pragma once

#include "GameObject.hpp"

class PhysicalObject : public GameObject
{
public:
    Layer collisionLayer;
    bool* collisionMask;
	Point2D speed;

	virtual void onStart() override;
	virtual void onUpdate() override;
    virtual void onCollision(PhysicalObject collider);

	PhysicalObject(Rect rect, Layer layer, char* sprite);
	PhysicalObject(Rect rect, Layer layer, char* sprite, Layer collisionLayer, Point2D speed = Point2D(0, 0), bool* collisionMask=NULL);
};