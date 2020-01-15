#pragma once

#include "GameObjects/PhysicalObject.hpp"

class RoadLine : public GameObject
{
private:
	bool tick = false;
public:
	void onStart() override;
	void onUpdate() override;

	RoadLine(Point2D position);
};