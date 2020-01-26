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

using std::chrono::milliseconds;
using std::chrono::milliseconds;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::this_thread::sleep_for;
using std::string;

std::chrono::time_point<std::chrono::steady_clock> GameEngine::lastLoopTime_;
int GameEngine::maxFps;
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
	GameEngine::deltaTime_ = 1 / (float)GameEngine::maxFps;
}

void GameEngine::changeScene(string name)
{
	if (name == "GameScene") {
		delete gameScene;
		gameScene = new GameScene();
		GameEngine::nextScene = gameScene;
	}
	else if (name == "MenuScene") {
		GameEngine::nextScene = menuScene;
	}
	else if (name == "GameOverScene") {
		GameEngine::nextScene = gameOverScene;
	}
}

void GameEngine::loop()
{
	//Cambio di scena (se necessario)
	if (GameEngine::nextScene != NULL) {
		GameEngine::currentScene = GameEngine::nextScene;
		GameEngine::nextScene = NULL;
		System::setTextColor(Color::No_Color, Color::No_Color);
		Graphics::clearBuffer();
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
	//Graphics::redrawScreen();

	if (GameEngine::currentScene != NULL) {
		GameEngine::currentScene->onEndLoop();
	}

	//Sincronizza con il clock di fps

	float expectedDeltaTime = 1 / (float)GameEngine::maxFps;

	float clockPrecision = (float)std::chrono::high_resolution_clock::period::num
		/ std::chrono::high_resolution_clock::period::den;

	auto currentTime = high_resolution_clock::now();
	auto elapsedTime = duration_cast<std::chrono::duration<float>>((currentTime - GameEngine::lastLoopTime_));

	if (elapsedTime.count() < expectedDeltaTime) {
		//Siamo in anticipo: sleep
		sleep_for(std::chrono::duration<float>(expectedDeltaTime - elapsedTime.count()));
		currentTime = high_resolution_clock::now();
		elapsedTime = duration_cast<std::chrono::duration<float>>((currentTime - GameEngine::lastLoopTime_));
	}

	GameEngine::deltaTime_ = max(elapsedTime.count(), clockPrecision);
	GameEngine::lastLoopTime_ = high_resolution_clock::now();
}

float GameEngine::deltaTime()
{
	return GameEngine::deltaTime_;
}