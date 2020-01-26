#pragma once
#include <GameObjects/GameObject.hpp>
#include <vector>

/// <summary>	Gestisce il comportamento
/// 			della strada. </summary>

class Road : public GameObject {
private:
	std::vector<Cell> newLine();
	int roadBeginning;
	int roadWidth;
public:

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="size">		   	La dimensione della Strada (non
	/// 							della carreggiata). </param>
	/// <param name="initialSpeed">	La velocità iniziale. </param>
	/// <param name="memory">	   	Quante righe della strada passata
	/// 							vengono memorizzate prima di essere
	/// 							eliminate. </param>

	Road(Size size, float initialSpeed, int memory);

	/// <summary>	Eseguito ogni ciclo del motore di gioco. </summary>
	///
	/// <remarks>	Utente, 26/01/2020. </remarks>

	void onUpdate();
};