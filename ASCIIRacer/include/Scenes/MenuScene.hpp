#pragma once
#include "Scenes/Scene.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Core/Typedefs.hpp"
#include "Core/Rect.hpp"
#include "windows.h"
#include <utility>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class MenuScene : public Scene {
private:
	/// <summary>	Le opzioni del menu. </summary>
	std::vector<std::pair<std::string, std::string>> options;

	/// <summary>	La posizione del cursore. </summary>
	int cursor = 0;

	/// <summary>	Lo sprite del titolo. </summary>
	Sprite titleSprite;

	/// <summary>	Il Rect del titolo. </summary>
	Rect titleRect;

	/// <summary>	Carica le opzioni del menu. </summary>

	void fetchOptions();

	/// <summary>	Disegna il menu. </summary>
	///
	/// <param name="xOffset">	L'offset x del menu. </param>
	/// <param name="yOffset">	L'offset y del menu. </param>

	void drawMenu(int xOffset, int yOffset);

	/// <summary>	Sposta il cursore del menu. </summary>
	///
	/// <param name="down">	True se il cursore
	/// 					è stato spostato in
	/// 					basso. </param>

	void moveCursor(bool down);

	/// <summary>	Aggiunge un'opzione. </summary>
	///
	/// <param name="name">		Il nome dell'opzione. </param>
	/// <param name="scene">   	Il nome della scena. </param>

	void addOption(std::string name, std::string scene);
public:
	/// <summary>	Viene chiamato quando la scena
	/// 			viene caricata. </summary>

	void onStart() override;

	/// <summary>	Viene chiamato ogni esecuzione
	/// 			del ciclo di gioco. </summary>
	///
	/// <remarks>	Non inserire codice legato
	/// 			alla grafica. </remarks>

	void onLoop() override;

	/// <summary>	Viene chiamato ogni esecuzione
	/// 			del ciclo di gioco, quando il
	/// 			motore è pronto per la grafica. </summary>
	///
	/// <remarks>	Non inserire codice non legato
	/// 			alla grafica. </remarks>

	void onGraphics() override;
};