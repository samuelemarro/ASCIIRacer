#pragma once

#include "GameObjects/PhysicalObject.hpp"

class RoadLine : public GameObject
{
public:
	void onStart() override;
	void onUpdate() override;

	RoadLine(Point2D position, char c);
};