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

/// <summary>	Gestisce l'esecuzione del gioco. </summary>

class GameEngine
{
private:

	/// <summary>	Costruttore di default (privato). </summary>

	GameEngine();

	/// <summary>	Il momento in cui il motore ha
	/// 			eseguito l'ultimo ciclo. </summary>
	static std::chrono::time_point<std::chrono::steady_clock> lastLoopTime_;

	/// <summary>	La prossima scena. </summary>
	static ptr_Scene nextScene;

	/// <summary>	Il tempo impiegato per l'esecuzione di
	/// 			un ciclo. </summary>
	static float deltaTime_;

public:

	/// <summary>	La scena di gioco. </summary>
	static GameScene* gameScene;

	/// <summary>	La scena di Game Over. </summary>
	static GameOverScene* gameOverScene;

	/// <summary>	La scena del menu. </summary>
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