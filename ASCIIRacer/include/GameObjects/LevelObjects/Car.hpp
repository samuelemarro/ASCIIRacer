#pragma once
#include "Core/Typedefs.hpp"
#include "PhysicalObject.hpp"

class Car : public PhysicalObject
{
public:
	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual void onCollision(PhysicalObject collider) override;
	Car(Rect rect, Layer layer, Sprite sprite);
	Car();
};