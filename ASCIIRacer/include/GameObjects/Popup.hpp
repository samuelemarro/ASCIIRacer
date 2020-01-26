#pragma once
#include "GameObjects/GameObject.hpp"

/// <summary>	Un GameObject che appare
/// 			per poco tempo, solitamente
/// 			per notificare il giocatore. </summary>

class Popup : public GameObject {
private:

	/// <summary>	Quanto tempo è passato
	/// 			dall'ultima chiamata di
	/// 			notify(). </summary>
	float shownTime;

	/// <summary>	Vero se il Popup è al
	/// 			momento attivo. </summary>
	bool active;

	/// <summary>	La durata della notifica
	/// 			attuale. </summary>
	float currentDuration;
public:

	void onUpdate() override;

	/// <summary>	Notifica il giocatore. </summary>
	///
	/// <param name="spritePath">	Il percorso del file dello sprite
	/// 							della notifica. </param>
	/// <param name="duration">  	La durata della notifica. </param>

	void notify(std::string spritePath, float duration);

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="position">	La posizione del Popup. </param>

	Popup(Point2D position);
};

typedef Popup* ptr_Popup;