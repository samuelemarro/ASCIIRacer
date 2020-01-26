#pragma once
#include "Engine/System.hpp"

using std::vector;

/// <summary>	Il livello che la PlayerCar percorre  </summary>

class Level {
private:

	/// <summary>	L'identificativo del prossimo oggetto da generare  </summary>
	int currentId;

	/// <summary>	il seed con cui inizializzare il generatore
	///				pseudo-random quando si passa a questo livello	</summary>
	unsigned int seed;

	/// <summary>	Probabilità di generazione di ogni tipo di oggetto per quadretto  </summary>
	float obstacleProbability[3] = { 0.001, 0.002, 0.002 };
	float upgradeProbability[2] = { 0.002, 0.001 };

	/// <summary>	Probabilità di generazione cumulative di quella classe di oggetto  </summary>
	float obstacleCumulative;
	float upgradeCumulative;
	float AIcarProbability;

	/// <summary>	Il danno in base alla classe e tipo di oggetto  </summary>
	int obstacleDamage[3];
	int upgradeBonus[2] = { 150, 300 };
	int AIDamage;

	/// <summary>	Punti necessari per passare rispettivamente al
	///				livello successivo e precedente	 </summary>
	int pointsToNextLevel;
	int pointsToPrevLevel;

public:

	/// <summary>	Velocità del livello  </summary>
	float speed;

	/// <summary>	Difficoltà del livello  </summary>
	int difficulty;

	/// <summary>	Insieme degli identificativi degli oggetti che
	///				sono stati raccolti/urtati in questo livello finora  </summary>
	vector<int> removedIds;

	/// <summary>	Puntatori al livello precedente e successivo rispettivamente </summary>
	Level* prevLevel;
	Level* nextLevel;

	/// <summary>	Costruttore di default  </summary>
	Level();

	/// <summary>	Costruttore  </summary>
	///
	/// <param name="ptn">		   	Punti per il livello successivo </param>
	/// <param name="ptp">			Punti per il livello precedente </param>
	/// <param name="s">	   		Velocità del livello  </param>
	/// <param name="d">			Difficoltà del livello  </param>
	Level(int ptn, int ptp, float s, int d);

	/// <summary>	Prepara il livello inizializzando seed e currentId  </summary>
	void prepareLevel();

	/// <summary>	Ritorna il livello verso cui bisogna fare la transizione,
	///				se necessario lo genera	 </summary>
	///
	/// <param name="player_points">	I punti attuali del giocatore  </param>
	Level* newLevel(int player_points);

	/// <summary>	Ritorna true se si deve cambiare livello, false altrimenti  </summary>
	///
	/// <param name="player_points">	I punti attuali del giocatore  </param>
	bool changeLevel(int player_points);

	///	<summary>	Genera gli oggetti per la prossima linea di strada	</summary>
	///
	///	<param name="roadPosition">		Posizione nella console del bordo sinistro
	///									della strada  </param>
	/// <param name="roadWidth">		Larghezza della strada	</param>
	void generateLine(int roadPosition, int roadWidth);
};

typedef Level* ptr_Level;