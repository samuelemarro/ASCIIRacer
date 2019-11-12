#include "GameObjects/LevelObjects/Car.hpp"

Car::Car() : PhysicalObject() {

}

Car::Car(Rect rect, Layer layer, Sprite sprite) : PhysicalObject(rect, layer, sprite)
{
}

void Car::onStart() {}
void Car::onUpdate() {}
void Car::onCollision(PhysicalObject collider) {}