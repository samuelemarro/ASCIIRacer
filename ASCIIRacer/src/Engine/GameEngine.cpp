#include <vector>
#include "GameEngine.hpp"
#include "Engine/LevelGenerator.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Engine/Graphics.hpp"
#include "GameObjects/GameObject.hpp"
#include "GameObjects/IKeyboard.hpp"

void GameEngine::GameLoop()
{
	//Costruzione
	LevelGenerator::UpdateLevel();

	//Keyboard
	KeyboardStatus* status = Keyboard::getStatus();

	//Fisica
	//Gioco
	//Grafica
	Graphics::clearBuffer();
	
	///TODO:Disegna oggetti

	//Finalizzazione
}

void GameEngine::AddObject(GameObject gameObject) {
	//Controlla se supporta la fisica
	
}