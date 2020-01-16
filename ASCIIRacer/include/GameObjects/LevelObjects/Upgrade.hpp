#pragma once

#include "GameObjects/PhysicalObject.hpp"

class Upgrade : public PhysicalObject {
public:
	int bonus;

	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_PhysicalObject collider) override;

	Upgrade(Point2D position, int b);
};