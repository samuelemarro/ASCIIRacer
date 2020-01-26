#include <iostream>

#include "Engine/Graphics.hpp"
#include "Engine/GameEngine.hpp"

/// <summary>	Il punto di ingresso principale per
/// 			l'applicazione. </summary>
///
/// <returns>	L'Exit Code (0 se il programma è
/// 			stato eseguito correttamente). </returns>

int main()
{
	System::initialise();
	Graphics::initialise();
	MenuScene menuScene;
	GameEngine::maxFps = 60;
	GameEngine::start(&menuScene);

	while (true)
	{
		GameEngine::loop();
	}

	return 0;
}