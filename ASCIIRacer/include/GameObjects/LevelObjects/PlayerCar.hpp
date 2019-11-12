#pragma once

#include "Car.hpp"
#include "IKeyboard.hpp"

class PlayerCar : public Car, public IKeyboard
{
public:
	void onStart() override;
	void onUpdate() override;
	void onCollision(PhysicalObject collider) override;
	bool keyUpdate(KeyboardStatus status) override;

	PlayerCar(Point2D position);
};