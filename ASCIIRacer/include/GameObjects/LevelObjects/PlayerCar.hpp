#pragma once

#include "Car.hpp"

class PlayerCar : public Car
{
public:
	void onStart() override;
	void onUpdate() override;
	void onCollision(PhysicalObject collider) override;

	PlayerCar(Point2D position);
};