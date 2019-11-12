#include <vector>
#include "GameEngine.hpp"
#include "Engine/LevelGenerator.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Engine/Graphics.hpp"
#include "GameObjects/GameObject.hpp"

using std::vector;

vector<GameObject> GameEngine::newGameObjects_;
vector<PhysicalObject> GameEngine::newPhysicalObjects_;

vector<GameObject> GameEngine::gameObjects;
vector<PhysicalObject> GameEngine::physicalObjects;

void GameEngine::GameLoop()
{
	//Costruzione
	LevelGenerator::UpdateLevel();

	//Keyboard
	Keyboard::updateStatus();

	//Fisica
	//Gioco
	//Grafica
	Graphics::clearBuffer();
	
	///TODO:Disegna oggetti

	//Finalizzazione
}

void GameEngine::AddGameObject(GameObject gameObject) {
	GameEngine::newGameObjects_.push_back(gameObject);
}

void GameEngine::AddPhysicalObject(PhysicalObject physicalObject) {
	GameEngine::newPhysicalObjects_.push_back(physicalObject);
}
