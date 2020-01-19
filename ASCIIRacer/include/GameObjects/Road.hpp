#pragma once
#include <GameObjects/GameObject.hpp>
#include <vector>

class Road : public GameObject {
private:
	std::vector<Cell> newLine();
public:
	int roadBeginning;
	int roadWidth;

	Road(Size size, float initialSpeed, int memory);

	void onUpdate();
};