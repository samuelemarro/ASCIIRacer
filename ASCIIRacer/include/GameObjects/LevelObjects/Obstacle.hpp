#pragma once

#include "GameObjects/GeneratedObject.hpp"

/// <summary>	Un ostacolo. </summary>

class Obstacle : public GeneratedObject {
public:

	/// <summary>	I punti tolti in caso di collisione
	/// 			con la PlayerCar. </summary>
	int damage;

	/// <summary>	Il tipo di ostacolo. </summary>
	int type;

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="position">	   	La posizione iniziale. </param>
	/// <param name="damage">	   	I punti tolti in caso di
	/// 							collisione con la PlayerCar. </param>
	/// <param name="type">		   	Il tipo di ostacolo. </param>
	/// <param name="parentLevel"> 	Il puntatore al livello
	/// 							che ha generato questo
	/// 							Obstacle. </param>
	/// <param name="generationId">	Il codice identificativo
	/// 							assegnato dal livello a questo
	/// 							Obstacle. </param>

	Obstacle(Point2D position, int damage, int type, ptr_Level parentLevel, int generationId);
};