#pragma once

#include "GameObjects/GameObject.hpp"

class RoadLine : public GameObject
{
public:
	void onStart() override;
	void onUpdate() override;

	RoadLine(Point2D position, char c);
};