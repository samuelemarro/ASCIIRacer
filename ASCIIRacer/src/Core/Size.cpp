#include "Size.hpp"

Size::Size(int width, int height) : width(width), height(height) {

}

Size::Size() : Size(-1, -1) {

}

int Size::length() {
	return this->width * this->height;
}