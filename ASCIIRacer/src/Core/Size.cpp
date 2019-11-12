#include "Size.hpp"

Size::Size(int width, int height) : width(width), height(height) {

}

int Size::length() {
	return this->width * this->height;
}