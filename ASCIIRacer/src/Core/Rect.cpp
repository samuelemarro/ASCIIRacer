#include "Core/Rect.hpp"
#include <cmath>
#include <vector>

using std::floor;
using std::vector;

Rect::Rect(Point2D position, Size size) : position(position), size(size) {

}

Rect::Rect(float positionX, float positionY, int width, int height) : position(Point2D(positionX, positionY)), size(Size(width, height)) {

}

bool Rect::containsPoint(Point2D point, bool snap)
{
	return containsPoint(point.x, point.y, snap);
}

bool Rect::containsPoint(float x, float y, bool snap)
{
	if (snap) {
		int gridX = (int)floor(x);
		int gridY = (int)floor(y);

		int posX = (int)floor(position.x);
		int posY = (int)floor(position.y);
		return (gridX >= posX && gridY >= posY && gridX < posX + size.width && gridY < posY + size.height);
	}
	else {
		return (x >= position.x && y >= position.y && x < position.x + size.width && y < position.y + size.height);
	}
}

Rect::Rect() {

}