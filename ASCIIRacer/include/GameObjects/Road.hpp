#pragma once
#include <GameObjects/GameObject.hpp>
#include <vector>

class Road : public GameObject {
private:
	std::vector<Cell> newLine();
	int roadBeginning;
	int roadWidth;
public:

	Road(Size size, float initialSpeed, int memory);

	void onUpdate();
};