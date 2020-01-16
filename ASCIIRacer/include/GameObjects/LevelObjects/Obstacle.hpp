#pragma once

#include "GameObjects/PhysicalObject.hpp"

class Obstacle : public PhysicalObject {
public:
	int damage;

	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_PhysicalObject collider) override;

	Obstacle(Point2D position, int d);
};