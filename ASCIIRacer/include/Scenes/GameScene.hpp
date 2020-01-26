#pragma once
#include "Core/CollisionInfo.hpp"
#include "GameObjects/GameObject.hpp"
#include "Scenes/Scene.hpp"
#include "Levels/Level.hpp"
#include "GameObjects/GeneratedObject.hpp"
#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/Popup.hpp"
#include "GameObjects/Road.hpp"

class GameScene : public Scene {
private:

	/// <summary>	Restituisce i Layer dei GameObject
	/// 			della scena. </summary>
	///
	/// <returns>	Un vettore con i Layer. </returns>

	std::vector<Layer> getLayers();

	/// <summary>	Il puntatore alla PlayerCar della
	/// 			scena. </summary>
	PlayerCar* playerCar;

	/// <summary>	Contatore per il bonus di punti
	/// 			per la strada percorsa. </summary>
	double travelBonus;

	/// <summary>	Il puntatore alla Road della
	/// 			scena. </summary>
	Road* road;

	/// <summary>	Gli oggetti generati dal livello. </summary>
	vector<ptr_GeneratedObject> otherObjects;

	/// <summary>	Il punteggio più alto ottenuto
	/// 			nella partita attuale. </summary>
	int bestScore;

	/// <summary>	Il puntatore al Popup della
	/// 			scena. </summary>
	ptr_Popup popup;

	/// <summary>	Buffer dei dati sulle collisioni. </summary>
	std::vector<std::vector<ptr_GameObject>> collisionBuffer;

	/// <summary>	Rimuove i GameObject segnati come
	/// 			da essere distrutti. </summary>

	void removeToBeDestroyed();

	/// <summary>	Aggiunge un GameObject al collisionBuffer. </summary>
	///
	/// <param name="gameObject">	Il GameObject da aggiungere. </param>

	void addToCollisionBuffer(ptr_GameObject gameObject);

	/// <summary>	Restituisce la matrice di collisioni
	/// 			per un GameObject. </summary>
	///
	/// <param name="gameObject">	Il GameObject considerato. </param>
	/// <param name="future">	 	Vero se deve usare la posizione futura,
	/// 							falso se deve usare la posizione attuale. </param>
	///
	/// <returns>	The collision matrix. </returns>

	vector<vector<ptr_GameObject>> getCollisionMatrix(ptr_GameObject gameObject, bool future);

	/// <summary>	Restituisce delle coppie
	/// 			(GameObject, CollisionType) per un
	/// 			dato GameObject. </summary>
	///
	/// <param name="gameObject">	Il GameObject considerato. </param>
	/// <param name="future">	 	Vero se deve usare la posizione futura,
	/// 							falso se deve usare la posizione attuale. </param>
	///
	/// <returns>	Le coppie (GameObject, CollisionType) . </returns>

	std::vector<std::pair<ptr_GameObject, CollisionType>> getCollisionPairs(ptr_GameObject gameObject, bool future);

	/// <summary>	Restituisce le informazioni
	/// 			sulle collisioni di un dato
	/// 			GameObject. </summary>
	///
	/// <param name="gameObject">	Il GameObject considerato. </param>
	///
	/// <returns>	Un vettore di informazioni sulle collisioni. </returns>

	std::vector<CollisionInfo> getCollisionInfos(ptr_GameObject gameObject);

	/// <summary>	Controlla le collisioni e chiama i rispettivi
	/// 			onCollision(). </summary>

	void checkCollisions();

	/// <summary>	Restituisce tutti i GameObjects. </summary>
	///
	/// <returns>	Un vettore contenente tutti i GameObject. </returns>

	vector<ptr_GameObject> getGameObjects();

	/// <summary>	Restituisce tutti i GameObject, tranne
	/// 			PlayerCar e Popup. </summary>
	///
	/// <returns>	Un vettore contenente tutti i GameObject,
	/// 			tranne PlayerCar e Popup. </returns>

	std::vector<ptr_GameObject> getLevelObjects();

public:

	/// <summary>	Il livello attuale. </summary>
	ptr_Level currentLevel;

	void increasePoints();
	void addGameObject(ptr_GeneratedObject gameObject);

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

	/// <summary>	Viene chiamato alla fine
	/// 			di ogni esecuzione del ciclo
	/// 			di gioco. </summary>

	void onEndLoop() override;

	/// <summary>	Distruttore. </summary>

	~GameScene();
};