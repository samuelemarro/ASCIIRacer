#pragma once

#include <vector>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/PhysicalObject.hpp"

class GameEngine
{
private:
	GameEngine();
	static std::vector<GameObject> newGameObjects_;
	static std::vector<PhysicalObject> newPhysicalObjects_;

public:
	static std::vector<GameObject> gameObjects;
	static std::vector<PhysicalObject> physicalObjects;

	static int fps;

	static int score;
	//Eventuali informazioni di gioco

	//Accetta oggetti o i loro puntatori?
	static void AddGameObject(GameObject gameObject);
	static void AddPhysicalObject(PhysicalObject physicalObject);

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