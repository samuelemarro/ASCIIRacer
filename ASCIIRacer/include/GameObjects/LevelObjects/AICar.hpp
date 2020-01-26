#pragma once

#include "Core/CollisionInfo.hpp"
#include "GameObjects/GeneratedObject.hpp"

/// <summary>	Un'automobile controllata dal computer. </summary>

class AICar : public GeneratedObject {
public:

	/// <summary>	I punti tolti in caso di collisione
	/// 			con la PlayerCar. </summary>
	int damage;

	/// <summary>	Eseguito ogni ciclo del motore
	/// 			di gioco. </summary>

	void onUpdate() override;

	/// <summary>	Chiamato in caso di collisione. </summary>
	///
	/// <param name="collisionInfo">	Le informazioni sulla collisione. </param>

	void onCollision(CollisionInfo collisionInfo);

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="position">	La posizione iniziale dell'AICar. </param>
	/// <param name="damage">	I punti tolti in caso di collisione
	/// 						con la PlayerCar. </param>

	AICar(Point2D position, int damage);
};