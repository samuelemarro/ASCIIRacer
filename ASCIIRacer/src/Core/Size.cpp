#include "Core/Size.hpp"

Size::Size(int width, int height) {
	this->width = width;
	this->height = height;
}

Size::Size() : Size(-1, -1) {
}