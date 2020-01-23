#pragma once

#include "GameObjects/GeneratedObject.hpp"

class Obstacle : public GeneratedObject {
public:
	int damage;
	int type;

	void onStart() override;
	void onUpdate() override;

	Obstacle(Point2D position, int d, int t, ptr_Level parentLevel, int generationId);
};