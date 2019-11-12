#include "Core/Rect.hpp"

Rect::Rect(Point2D position, Size size) : position(position), size(size) {

}

Rect::Rect(float positionX, float positionY, int width, int height) : position(Point2D(positionX, positionY)), size(Size(width, height)) {

}

Rect::Rect() : Rect(0, 0, 0, 0) {

}