#include "Core/Rect.hpp"
#include <vector>

using std::vector;

Rect::Rect(Point2D position, Size size) {
	this->position = position;
	this->size = size;
}

Rect::Rect(float positionX, float positionY, int width, int height) {
	this->position = Point2D(positionX, positionY);
	this->size = Size(width, height);
}

bool Rect::containsPoint(Point2D point, bool snap)
{
	return containsPoint(point.x, point.y, snap);
}

bool Rect::containsPoint(float x, float y, bool snap)
{
	if (snap) {
		int gridX = (int)(x);
		int gridY = (int)(y);

		int posX = (int)(position.x);
		int posY = (int)(position.y);
		return (gridX >= posX && gridY >= posY && gridX < posX + size.width && gridY < posY + size.height);
	}
	else {
		return (x >= position.x && y >= position.y && x < position.x + size.width && y < position.y + size.height);
	}
}

Rect::Rect() {
}