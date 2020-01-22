#include <thread>

#include "Scenes/GameOverScene.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/MenuScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/KeyboardStatus.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/System.hpp"
#include "GameObjects/GameObject.hpp"
#include "Core/Utilities.hpp"

using std::chrono::milliseconds;
using std::chrono::milliseconds;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::this_thread::sleep_for;
using std::string;

std::chrono::time_point<std::chrono::steady_clock> GameEngine::lastLoopTime_;
int GameEngine::fps;
ptr_Scene GameEngine::currentScene;
ptr_Scene GameEngine::nextScene;
//Fetch delle Scenes
GameScene* GameEngine::gameScene = new GameScene();
MenuScene* GameEngine::menuScene = new MenuScene();
GameOverScene* GameEngine::gameOverScene = new GameOverScene();
float GameEngine::deltaTime_;

void GameEngine::start(ptr_Scene firstScene) {
	//Qui va il codice di inizio gioco
	GameEngine::lastLoopTime_ = high_resolution_clock::now();
	GameEngine::currentScene = firstScene;
	GameEngine::nextScene = NULL;
	GameEngine::deltaTime_ = 1 / GameEngine::fps;
}

void GameEngine::changeScene(string name)
{
	if (name == "GameScene") {
		delete gameScene;
		gameScene = new GameScene();
		GameEngine::nextScene = gameScene;
	}
	else if(name == "MenuScene") GameEngine::nextScene = menuScene;
	else if(name == "GameOverScene") GameEngine::nextScene = gameOverScene;
}

void GameEngine::loop()
{
	//Cambio di scena (se necessario)
	if (GameEngine::nextScene != NULL) {
		GameEngine::currentScene = GameEngine::nextScene;
		GameEngine::nextScene = NULL;
		Graphics::clearBuffer();
		System::clearScreen();
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

	milliseconds expectedDeltaTime = milliseconds((int)1000 / GameEngine::fps);

	auto currentTime = high_resolution_clock::now();
	milliseconds elapsedTime = duration_cast<milliseconds>((currentTime - GameEngine::lastLoopTime_));
	milliseconds sleepTime = expectedDeltaTime - elapsedTime;
	if (sleepTime.count() > 0) {
		sleep_for(sleepTime);
	}
	//GameEngine::deltaTime_ = max((float)elapsedTime.count() / 1000, (float)expectedDeltaTime.count() / 1000);
	//GameEngine::deltaTime_ = (float)expectedDeltaTime.count() / 1000;
	GameEngine::lastLoopTime_ = high_resolution_clock::now();
}

float GameEngine::deltaTime()
{
	return 1 / (float)GameEngine::fps;
}
