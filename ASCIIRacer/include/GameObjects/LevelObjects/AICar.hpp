#pragma once

#include "Car.hpp"

class AICar : public Car
{
public:
	void onStart() override;
	void onUpdate() override;
	void onCollision(PhysicalObject collider) override;

	AICar(Point2D position);
};