#pragma once

#include "Core/Position.hpp"
#include "Core/Size.hpp"

class Rect {
public:
	Point2D position;
	Size size;

	Rect(Point2D position, Size size);
	Rect(float positionX, float positionY, int width, int height);
};