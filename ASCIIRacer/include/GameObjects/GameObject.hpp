#pragma once

#include "Core/Layer.hpp"
#include "Core/Rect.hpp"
#include "Core/Typedefs.hpp"
#include <string>

using std::string;
using std::to_string;

class GameObject {
public:

	/// <summary>	Il nome del GameObject. </summary>
	string name;

	/// <summary>	Il rettangolo del GameObject. </summary>
	Rect rect;

	/// <summary>	Il layer del GameObject, corrispondente
	/// 			alla posizione "z" </summary>
	Layer layer;

	/// <summary>	Lo sprite del GameObject. </summary>
	Sprite sprite;

	/// <summary>	Vero se il GameObject va eliminato alla fine
	/// 			del ciclo corrente. </summary>
	bool toBeDestroyed;

	/// <summary>	Vero se il GameObject "ferma" gli altri oggetti
	/// 			durante le collisioni. </summary>
	bool solid;

	/// <summary>	Il vettore velocità del GameObject. </summary>
	Point2D velocity;

	/// <summary>	Eseguito ogni ciclo del motore di gioco. </summary>

	virtual void onUpdate();

	/// <summary>	La posizione che il GameObject avrà nella prossima
	/// 			esecuzione del ciclo. </summary>
	///
	/// <remarks>	La posizione viene calcolata basandosi su
	/// 			<see cref="velocity">. </remarks>
	///
	/// <returns>	La posizione futura. </returns>

	Point2D futurePosition();

	/// <summary>	Costruttore di default. </summary>

	GameObject();
};

typedef GameObject* ptr_GameObject;