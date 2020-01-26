#include "Core/Point2D.hpp"
#include <cmath>

using std::sqrt;

Point2D::Point2D(float x, float y) : x(x), y(y) {
}

Point2D::Point2D() : Point2D(0, 0) {
}

float Point2D::magnitude() {
	return sqrt(x * x + y * y);
}