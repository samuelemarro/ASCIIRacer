#include <Engine/GameEngine.hpp>
#include <GameObjects/Road.hpp>

using std::vector;
using std::rand;

vector<Cell> Road::newLine()
{
	bool left = false;
	bool right = false;
	int r = rand() % 4;
	if (r == 0) {
		this->roadBeginning++;
		right = true;
	}
	else if (r == 1) {
		this->roadBeginning--;
		left = true;
	}

	if (this->roadBeginning < 0) {
		left = false;
		this->roadBeginning = 0;
	}
	else if (this->roadBeginning > 30) {
		right = false;
		this->roadBeginning = 30;
	}

	vector<Cell> roadPiece;
	for (int i = 0; i < rect.size.width; i++) {
		if (left && (i == this->roadBeginning || i == this->roadBeginning+this->roadWidth - 1)) {
			roadPiece.push_back(Cell('À', true));
			roadPiece.push_back(Cell('¿', true));
		}
		else if(!left && !right && (i == this->roadBeginning || i == this->roadBeginning + this->roadWidth)) {
			roadPiece.push_back(Cell('³', true));
		}
		else if (right && (i == this->roadBeginning-1 || i == this->roadBeginning + this->roadWidth - 2)) {
			roadPiece.push_back(Cell('Ú', true));
			roadPiece.push_back(Cell('Ù', true));
		}
		else {
			bool insideRoad = (i >= this->roadBeginning && i < this->roadBeginning + this->roadWidth);
			roadPiece.push_back(Cell(IGNORE_CHAR, !insideRoad));
		}
	}
	// TEST CON STRADA DRITTA (commentare parte sopra)
	/*vector<Cell> roadPiece;
	for (int i = 0; i < rect.size.width; i++) {
		if (i == this->roadBeginning || i == this->roadBeginning + this->roadWidth) {
			roadPiece.push_back(Cell('³', true));
		}
		else {
			roadPiece.push_back(Cell(IGNORE_CHAR, false));
		}
	}*/
	return roadPiece;
}

Road::Road(Size size, float initialSpeed, int memory) {
	Point2D position = Point2D(0, -1);
	Size trueSize = Size(size.width, size.height + memory);
	this->rect = Rect(position, trueSize);
	this->name = "Road";

	this->roadBeginning = 10;
	this->roadWidth = 50;

	this->sprite = vector<vector<Cell>>();
	for (int i = 0; i < rect.size.height; i++) {
		sprite.insert(sprite.begin(), newLine());
	}

	this->velocity = Point2D(0, initialSpeed);
	this->solid = true;
}

void Road::onUpdate() {
	while ((int)this->futurePosition().y >= 0) {
		this->rect.position.y -= 1;
		vector<Cell> roadPiece = newLine();
		sprite.insert(sprite.begin(), roadPiece);
		sprite.erase(sprite.end() - 1);

		//Chiama la generazione del livello
		((GameScene*)GameEngine::currentScene)->currentLevel->generateLine(this->roadBeginning, this->roadWidth);
		((GameScene*)GameEngine::currentScene)->increasePoints();
	}
}