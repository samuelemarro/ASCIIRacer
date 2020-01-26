#pragma once

#include <vector>
#include <chrono>
#include <string>
#include "Scenes/GameScene.hpp"
#include "Scenes/GameOverScene.hpp"
#include "Scenes/MenuScene.hpp"

#include "GameObjects/GameObject.hpp"
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"

class GameEngine
{
private:

	GameEngine();
	static std::chrono::time_point<std::chrono::steady_clock> lastLoopTime_;

	static ptr_Scene nextScene;

	static float deltaTime_;

public:
	static GameScene* gameScene;
	static GameOverScene* gameOverScene;
	static MenuScene* menuScene;

	/// <summary>	La scena attuale. </summary>
	static ptr_Scene currentScene;

	/// <summary>	Gli FPS massimi. </summary>
	static int maxFps;

	/// <summary>	Avvia il motore. </summary>
	///
	/// <param name="firstScene"> La prima scena. </param>

	static void start(ptr_Scene firstScene);

	/// <summary>	Cambia la scena. </summary>
	///
	/// <remarks>	Il cambio non è istantaneo: il motore
	/// 			finisce prima il ciclo corrente. </remarks>
	///
	/// <param name="name">	Il nome della scena da caricare. </param>

	static void changeScene(std::string name);

	/// <summary>	Il ciclo principale del motore. </summary>

	static void loop();

	/// <summary>	Restituisce il tempo (in secondi) trascorso dall'ultimo ciclo. </summary>
	///
	/// <returns>	Il tempo in secondi dall'ultimo ciclo completato. </returns>

	static float deltaTime();
};