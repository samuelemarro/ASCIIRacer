#pragma once

#include "GameObjects/GeneratedObject.hpp"

class Obstacle : public GeneratedObject {
public:
	int damage;

	void onStart() override;
	void onUpdate() override;

	Obstacle(Point2D position, int d, ptr_Level parentLevel, int generationId);
};