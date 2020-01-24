#pragma once

/// <summary>	Rappresenta una coppia di coordinate. </summary>

class Point2D {
public:

	/// <summary>	La coordinata x. </summary>
	float x;

	/// <summary>	La coordinata y. </summary>
	float y;

	Point2D(float x, float y);
	Point2D();

	float magnitude();
};