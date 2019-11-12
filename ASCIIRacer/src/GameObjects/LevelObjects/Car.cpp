#include "GameObjects/LevelObjects/Car.hpp"

Car::Car(Rect rect, Layer layer, char* sprite) : PhysicalObject(rect, layer, sprite)
{
}

void Car::onStart() {}
void Car::onUpdate() {}
void Car::onCollision(PhysicalObject collider) {}