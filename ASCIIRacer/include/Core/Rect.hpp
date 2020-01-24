#pragma once

#include "Core/Point2D.hpp"
#include "Core/Size.hpp"

class Rect {
public:

	/// <summary>	La posizione del vertice in alto
	/// 			a sinistra. </summary>
	Point2D position;

	/// <summary>	La dimensione. </summary>
	Size size;

	Rect();
	Rect(Point2D position, Size size);
	Rect(float positionX, float positionY, int width, int height);

	bool containsPoint(Point2D point, bool snap);
	bool containsPoint(float x, float y, bool snap);
};