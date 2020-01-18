#include <Engine/GameEngine.hpp>
#include <GameObjects/Road.hpp>

using std::vector;
using std::rand;

vector<Cell> Road::newLine()
{
	int r = rand() % 4;
	if (r == 0) {
		this->roadBeginning++;
	}
	else if (r == 1) {
		this->roadBeginning--;
	}

	if (this->roadBeginning < 0) {
		this->roadBeginning = 0;
	}


	vector<Cell> roadPiece;
	for (int i = 0; i < rect.size.width; i++) {
		if (i == this->roadBeginning || i == this->roadBeginning + this->roadWidth) {
			roadPiece.push_back(Cell('X', true));
		}
		else {
			roadPiece.push_back(Cell(IGNORE_CHAR, false));
		}
	}
	return roadPiece;
}

Road::Road(Size size, float initialSpeed) {
	Point2D position = Point2D(0, -1);
	this->rect = Rect(position, size);

	this->sprite = vector<vector<Cell>>();
	for (int i = 0; i < rect.size.height; i++) {
		sprite.insert(sprite.begin(), newLine());
	}

	this->velocity = Point2D(0, initialSpeed);
	this->immovable = true;

	this->roadBeginning = 10;
	this->roadWidth = 50;
}

void Road::onUpdate() {
	if (this->rect.position.y + this->velocity.y * GameEngine::deltaTime() >= 0) {
		this->rect.position.y = -1;
		vector<Cell> roadPiece = newLine();
		sprite.insert(sprite.begin(), roadPiece);
		sprite.erase(sprite.end() - 1);
	}
}