#pragma once

#include <vector>

#include "GameObjects/GameObject.hpp"
#include "Engine/GameObjectTracker.hpp"

class GameEngine
{
private:
	GameEngine();

public:
	static std::vector<GameObjectTracker> trackedObjects;

	static int fps;
	static int score;
	//Eventuali informazioni di gioco

	/**
	 * @brief Aggiunge un oggetto al motore.
	 *
	 * Verrà aggiunto solo all'inizio del ciclo successivo.
	 * Ogni oggetto aggiunto riceve la chiamata di onStart().
	 *
	 * @param newObject L'oggetto da aggiungere.
	 */
	static void AddObject(GameObject newObject);

	/**
	 * @brief Rimuove un oggetto dal motore e lo elimina.
	 *
	 * Verrà rimosso solo alla fine del ciclo.
	 *
	 * @param object L'oggetto da rimuovere.
	 */
	static void DestroyObject(GameObject object);

	static void Start();

	static void GameLoop();
};