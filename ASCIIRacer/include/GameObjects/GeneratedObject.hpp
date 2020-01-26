#pragma once

#include "Levels/Level.hpp"
#include "GameObjects/GameObject.hpp"

/// <summary>	Un oggetto generato da <see cref="Level">. </summary>

class GeneratedObject : public GameObject {
public:

	/// <summary>	Il puntatore al livello che ha generato
	/// 			questo GeneratedObject. </summary>
	ptr_Level parentLevel;

	/// <summary>	Il codice identificativo assegnato
	/// 			dal livello a questo GeneratedObject. </summary>
	int generationId;

	void onUpdate() override;

	/// <summary>	Costruttore di default. </summary>

	GeneratedObject();

	/// <summary>	Costruttore completo. </summary>
	///
	/// <param name="parentLevel"> 	Il puntatore al livello
	/// 							che ha generato questo
	/// 							GeneratedObject. </param>
	/// <param name="generationId">	Il codice identificativo
	/// 							assegnato dal livello a questo
	/// 							GeneratedObject. </param>

	GeneratedObject(ptr_Level parentLevel, int generationId);
};

typedef GeneratedObject* ptr_GeneratedObject;