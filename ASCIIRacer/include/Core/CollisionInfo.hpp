#pragma once

#include "GameObjects/GameObject.hpp"
#include "Core/CollisionType.hpp"

/// <summary>	Contiene informazioni su una particolare collisione. </summary>

class CollisionInfo {
public:

	/// <summary>	Il puntatore al GameObject con cui è
	/// 			avvenuta la collisione. </summary>
	ptr_GameObject collider;

	/// <summary>	Il tipo di collisione che avverrà se
	/// 			il GameObject non si muove. </summary>
	CollisionType present;

	/// <summary>	Il tipo di collisione che avverrà se
	/// 			il GameObject si muove. </summary>
	CollisionType future;

	/// <summary>	Costruttore di base. </summary>
	///
	/// <remarks>	Inizializza present e future a dei
	/// 			CollisionType vuoti. </remarks>
	///
	/// <param name="collider">	Il puntatore al GameObject con
	/// 						cui è avvenuta la collisione. </param>

	CollisionInfo(ptr_GameObject collider);

	/// <summary>	Costruttore completo. </summary>
	///
	/// <remarks>	Utente, 26/01/2020. </remarks>
	///
	/// <param name="collider">	Il puntatore al GameObject con
	/// 						cui è avvenuta la collisione. </param>
	/// <param name="present"> 	Il tipo di collisione che avverrà se il
	/// 						GameObject non si muove. </param>
	/// <param name="future">  	Il tipo di collisione che avverrà se il
	/// 						GameObject si muove. </param>

	CollisionInfo(ptr_GameObject collider, CollisionType present, CollisionType future);
};