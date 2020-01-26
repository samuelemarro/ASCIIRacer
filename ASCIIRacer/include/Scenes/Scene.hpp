#pragma once
#include <iostream>

class Scene {
public:

	/// <summary>	Vero se la scena è inizializzata. </summary>
	bool initialised = false;

	/// <summary>	Viene chiamato quando la scena
	/// 			viene caricata. </summary>

	virtual void onStart();

	/// <summary>	Viene chiamato ogni esecuzione
	/// 			del ciclo di gioco. </summary>
	///
	/// <remarks>	Non inserire codice legato
	/// 			alla grafica. </remarks>

	virtual void onLoop();

	/// <summary>	Viene chiamato ogni esecuzione
	/// 			del ciclo di gioco, quando il
	/// 			motore è pronto per la grafica. </summary>
	///
	/// <remarks>	Non inserire codice non legato
	/// 			alla grafica. </remarks>

	virtual void onGraphics();

	/// <summary>	Viene chiamato alla fine
	/// 			di ogni esecuzione del ciclo
	/// 			di gioco. </summary>

	virtual void onEndLoop();
};

typedef Scene* ptr_Scene;