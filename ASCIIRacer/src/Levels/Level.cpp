#include "Levels/Level.hpp"

Level::Level() {
	this->prevLevel = nullptr;
	this->nextLevel = nullptr;
	this->slicesCount = 0;
}

Level::Level(int ptn, int ptp, double s, int d) : Level(){
	this->pointsToNextLevel = ptn;
	this->pointsToPrevLevel = ptp;
	this->speed = s;
	this->difficulty = d;
}

bool Level::changeLevel(int player_points) {
	return (player_points >= this->pointsToNextLevel) || (player_points <= this->pointsToPrevLevel);
}

Level* Level::NextLevel(int player_points) {
	if (player_points >= this->pointsToNextLevel) {
		Level* nl = new Level(pointsToNextLevel + 100*(difficulty + 1), pointsToNextLevel * 0.90, speed + 1, difficulty + 1);
		this->nextLevel = nl;
		nl->prevLevel = this;
		return nl;
	}

	else if (player_points <= this->pointsToPrevLevel) {
		return this->prevLevel;
	}

	else return 0;		//Caso mai raggiunto poichè precondition: changeLevel == true
}

void Level::generateMap() {

	//bool grid[50][30] = {0};

	int obstacles_number = 29 + this->difficulty;
	int upgrades_number = 29;

	for (int i = 0; i < obstacles_number; ++i) {

		int x = rand() % 49 + 1;
		int y = rand() % 30;

		Obstacle* obstacle = new Obstacle(Point2D(x, y), this->difficulty * 15);    //dato da speed * 2(sec che voglio che mi riduca per dover arrivare al next)
		obstacle->velocity.y = this->speed;
		obstacle->velocity.x = 0;
		this->mapSlice.push_back(obstacle);
	}

	for (int i = 0; i < upgrades_number; ++i) {

		int x = rand() % 49 + 1;
		int y = rand() % 30;

		Upgrade* upgrade = new Upgrade(Point2D(x, y), this->difficulty * 10);
		upgrade->velocity.y = this->speed;
		upgrade->velocity.x = 0;
		this->mapSlice.push_back(upgrade);
	}
}

void Level::saveMap() {
	Map.push_back(mapSlice);

	this->mapSlice.clear();
}

vector<ptr_GameObject> Level::getMapLine(int roadIndex, ptr_GameObject Road_object, bool generateMap) {
	Road* road = dynamic_cast<Road*>(Road_object);

	if (generateMap) {
		this->slicesCount += 1;
		this->saveMap();
		this->generateMap();
	}

	//get and return all elements of that line from mapSlice depending on roadIndex, shifted right or left depending on the road object in that position
	vector<ptr_GameObject> Line;
	for (auto gameObject : this->mapSlice) {				//la correttezza di questo sotto è da verificare
		if (gameObject->rect.position.y  == 29 - (roadIndex % 30)) {
			gameObject->rect.position.y -= 30 * this->slicesCount;
			gameObject->rect.position.x += road->roadBeginning;
			
			GameObject* g = gameObject;
			g->rect.position.y = -1;
			Line.push_back(gameObject);
		}
	}

	if (Line.size() != 2) {
		int j = 0;
	}

	return Line;
}

void Level::saveObject(ptr_GameObject gameObject) {
	int j = 69; //TODO
}