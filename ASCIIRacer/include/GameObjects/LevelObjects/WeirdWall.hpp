#pragma once
#include "GameObjects/PhysicalObject.hpp"

class WeirdWall : public PhysicalObject {
public:
	WeirdWall(Point2D position, float speed);

	float speed;

	void onStart() override;
	void onUpdate() override;
	void onCollision(PhysicalObject* collider);
};