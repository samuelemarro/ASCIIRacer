#include "GameObjects/LevelObjects/PlayerCar.hpp"

const Size playerCarSize = Size(3, 3);
char playerCarSprite[] = "/-\\|O|\\-/";
Layer playerCarLayer = Layer::Content;

PlayerCar::PlayerCar(Point2D position) : Car(Rect(position, playerCarSize), playerCarLayer, playerCarSprite) {
	
}

bool PlayerCar::keyUpdate(KeyboardStatus status) { 
	return true;
}

void PlayerCar::onStart() {}
void PlayerCar::onUpdate() {}
void PlayerCar::onCollision(PhysicalObject collider) {}