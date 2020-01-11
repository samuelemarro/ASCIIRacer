#include <thread>

#include "Engine/GameEngine.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Engine/Graphics.hpp"
#include "GameObjects/GameObject.hpp"
#include "Core/Utilities.hpp"

using std::chrono::milliseconds;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::this_thread::sleep_for;

std::chrono::time_point<std::chrono::steady_clock> GameEngine::lastLoopTime_;
int GameEngine::fps;
ptr_Scene GameEngine::currentScene;
ptr_Scene GameEngine::nextScene;

void GameEngine::start(ptr_Scene firstScene) {
	//Qui va il codice di inizio gioco
	GameEngine::lastLoopTime_ = high_resolution_clock::now();
	GameEngine::currentScene = firstScene;
	GameEngine::nextScene = NULL;
}

void GameEngine::changeScene(ptr_Scene newScene)
{
	GameEngine::nextScene = newScene;
}

void GameEngine::loop()
{
	//Cambio di scena (se necessario)
	if (GameEngine::nextScene != NULL) {
		GameEngine::currentScene = GameEngine::nextScene;
		GameEngine::nextScene = NULL;
	}

	//Inizializzazione della scena
	if (GameEngine::currentScene != NULL && !GameEngine::currentScene->initialised) {
		GameEngine::currentScene->onStart();
		GameEngine::currentScene->initialised = true;
	}

	//Keyboard
	Keyboard::updateStatus();

	if (GameEngine::currentScene != NULL) {
		GameEngine::currentScene->onLoop();
	}

	//Grafica
	Graphics::clearBuffer();

	if (GameEngine::currentScene != NULL) {
		GameEngine::currentScene->onGraphics();
	}
	
	Graphics::updateScreen();

	if (GameEngine::currentScene != NULL) {
		GameEngine::currentScene->onEndLoop();
	}


	//Sincronizza con il clock di fps

	milliseconds expectedDeltaTime = milliseconds(1000 / GameEngine::fps);

	auto currentTime = high_resolution_clock::now();
	milliseconds elapsedTime = duration_cast<milliseconds>((currentTime - GameEngine::lastLoopTime_));
	milliseconds sleepTime = expectedDeltaTime - elapsedTime;
	sleep_for(sleepTime);
	GameEngine::lastLoopTime_ = high_resolution_clock::now();
}

float GameEngine::deltaTime()
{
	return 1 / (float)GameEngine::fps;
}
