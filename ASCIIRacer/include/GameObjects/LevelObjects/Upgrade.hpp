#pragma once

#include "GameObjects/GeneratedObject.hpp"

/// <summary>	Un bonus. </summary>

class Upgrade : public GeneratedObject {
public:

	/// <summary>	I punti aggiunti in caso
	/// 			di collisione con la PlayerCar. </summary>
	int bonus;


	/// <summary>	Il tipo di Upgrade. </summary>
	int type;

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="position">	   	The position. </param>
	/// <param name="bonus">	   	I punti aggiunti in caso di
	/// 							collisione con la PlayerCar. </param>
	/// <param name="type">		   	Il tipo di Upgrade. </param>
	/// <param name="parentLevel"> 	Il puntatore al livello
	/// 							che ha generato questo
	/// 							Upgrade. </param>
	/// <param name="generationId">	Il codice identificativo
	/// 							assegnato dal livello a questo
	/// 							Upgrade. </param>

	Upgrade(Point2D position, int bonus, int type, ptr_Level parentLevel, int generationId);
};