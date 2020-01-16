#pragma once

#include "GameObjects/PhysicalObject.hpp"

class Border : public PhysicalObject {
public:
	int roadWidth;

	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_PhysicalObject collider) override;

	Border(Point2D position, int rw);
};