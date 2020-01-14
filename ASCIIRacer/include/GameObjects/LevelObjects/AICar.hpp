#pragma once

#include "GameObjects/PhysicalObject.hpp"

class AICar : public PhysicalObject
{
public:
	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_PhysicalObject collider) override;

	AICar(Point2D position);
};