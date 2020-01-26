#pragma once
#include <GameObjects/GameObject.hpp>
#include <vector>

/// <summary>	Gestisce il comportamento
/// 			della strada. </summary>

class Road : public GameObject {
private:

	/// <summary>	Genera una nuovo pezzo di strada. </summary>
	/// <returns>	Un vettore con le celle del
	/// 			pezzo di strada. </returns>

	std::vector<Cell> newLine();

	/// <summary>	La posizione in cui inizia la strada. </summary>
	int roadBeginning;

	/// <summary>	La larghezza della strada. </summary>
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