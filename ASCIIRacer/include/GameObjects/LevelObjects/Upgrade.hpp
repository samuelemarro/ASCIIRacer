#pragma once

#include "GameObjects/GeneratedObject.hpp"

class Upgrade : public GeneratedObject {
public:
	int bonus;

	void onStart() override;
	void onUpdate() override;

	Upgrade(Point2D position, int b, ptr_Level parentLevel, int generationId);
};