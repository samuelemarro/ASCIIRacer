#include "Levels/Level.hpp"

#include "Engine/GameEngine.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "GameObjects/LevelObjects/AICar.hpp"

#include <numeric>
using std::rand;
using std::accumulate;

Level::Level() {
	this->prevLevel = nullptr;
	this->nextLevel = nullptr;
	this->currentId = 0;
	this->seed = -1;
}

Level::Level(int ptn, int ptp, float s, int d) : Level() {
	this->pointsToNextLevel = ptn;
	this->pointsToPrevLevel = ptp;
	this->speed = s;
	this->difficulty = d;

	// Aggiustamento delle probabilità di generazione in base alla difficoltà
	for (int i = 0; i < 3; ++i)
		obstacleProbability[i] = min(obstacleProbability[i] + (this->difficulty - 1) * 0.000025f, obstacleProbability[i] / 5.0f * 7.0f);
	obstacleCumulative = accumulate(obstacleProbability, obstacleProbability + 3, 0.0f);

	for (int i = 0; i < 2; ++i)
		upgradeProbability[i] = max(upgradeProbability[i] - (this->difficulty - 1) * 0.000025f, upgradeProbability[i] / 3.0f);
	upgradeCumulative = accumulate(upgradeProbability, upgradeProbability + 2, 0.0f);

	AIcarProbability = min(0.0005f + 0.000025f * this->difficulty, 0.001f);

	//	Aggiustamento dei danni degli ostacoli e macchine in base alla difficoltà
	for (int i = 0; i < 3; ++i)
		obstacleDamage[i] = min(150 + 75 * (2 - i) + 25 * (this->difficulty - 1), 250 + 125 * (2 - i));

	AIDamage = min(500 + 50 * (this->difficulty - 1), 1000);
}

bool Level::changeLevel(int player_points) {
	return (player_points >= this->pointsToNextLevel) || (player_points <= this->pointsToPrevLevel);
}

void Level::prepareLevel()
{
	// Se è un nuovo livello, inizializza il suo seed, e srand con esso
	if (this->seed == -1) {
		this->seed = time(NULL);
	}
	srand(this->seed);

	// Ri-inizializza currentId a 0 (poichè ri-generi gli stessi oggetti ogni volta)
	this->currentId = 0;
}

Level* Level::newLevel(int player_points) {
	// Precondition: changeLevel == true

	// Se i punti bastano a passare al livello successivo
	if (player_points >= this->pointsToNextLevel) {
		// Se non esiste un livello successivo lo genero
		if (this->nextLevel == NULL) {
			Level* new_level = new Level(pointsToNextLevel + 1000, pointsToNextLevel - 100, min(speed + 1, 30), difficulty + 1);
			this->nextLevel = new_level;
			new_level->prevLevel = this;
			new_level->nextLevel = NULL;
			return new_level;
		}

		// Altrimenti lo ritorno
		else
			return this->nextLevel;
	}

	// Altrimenti ritorna il livello precedente
	else
		return this->prevLevel;
}

void Level::generateLine(int roadPosition, int roadWidth) {
	GameScene* scene = (GameScene*)GameEngine::currentScene;

	// Per ogni quadretto della strada
	for (int i = 1; i < roadWidth; i++) {
		// Genero un numero random fra 0 e 1
		float r = System::randomFloat();

		// Eventualmente genera ostacolo
		if (r < obstacleCumulative) {
			bool placed = false;

			// Genera ostacolo in base al tipo
			for (int j = 1; j <= 3 && !placed; j++) {
				if (r < accumulate(obstacleProbability, obstacleProbability + j, 0.0)) {
					Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, -1), obstacleDamage[j - 1], j, this, currentId);
					obstacle->velocity.y = this->speed;
					obstacle->velocity.x = 0;

					i += obstacle->rect.size.width - 1;

					// Se non esce dalla strada e non è stato precedentemente rimosso, aggiungilo alla scena
					if ((i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()))
					{
						scene->addGameObject(obstacle);
					}
					else
					{
						delete obstacle;
					}

					placed = true;

					// Se era un muro, crea anche fino ad altri 4 muri alla sua destra
					if (j == 3) {
						for (int k = 0; k < 4; k++) {
							currentId++;
							i++;
							Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, -1), obstacleDamage[j - 1], j, this, currentId);
							obstacle->velocity.y = this->speed;
							obstacle->velocity.x = 0;

							i += obstacle->rect.size.width - 1;
							if ((i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()))
								scene->addGameObject(obstacle);
							else
								delete obstacle;
						}
					}

					// Se era una spike, creane un' altra alla sua destra
					else if (j == 1) {
						currentId++;
						i++;
						Obstacle* obstacle = new Obstacle(Point2D(roadPosition + i, -1), obstacleDamage[j - 1], j, this, currentId);
						obstacle->velocity.y = this->speed;
						obstacle->velocity.x = 0;

						i += obstacle->rect.size.width - 1;
						if ((i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()))
							scene->addGameObject(obstacle);
						else
							delete obstacle;
					}
				}
			}

			// Incrementa l'id poichè ho generato un oggetto
			currentId++;
		}

		// Altrimenti, eventualmente genera upgrade
		else if (r < obstacleCumulative + upgradeCumulative) {
			bool placed = false;

			// Genera upgrade in base al tipo
			for (int j = 1; j <= 2 && !placed; j++) {
				if (r < obstacleCumulative + accumulate(upgradeProbability, upgradeProbability + j, 0.0)) {
					Upgrade* upgrade = new Upgrade(Point2D(roadPosition + i, -1), 150 + 150 * (j - 1), j, this, currentId);
					upgrade->velocity.y = this->speed;
					upgrade->velocity.x = 0;

					i += upgrade->rect.size.width - 1;

					// Se non esce dalla strada e non è stato precedentemente rimosso, aggiungilo alla scena
					if ((i < roadWidth) && (find(this->removedIds.begin(), this->removedIds.end(), this->currentId) == this->removedIds.end()))
						scene->addGameObject(upgrade);
					else
						delete upgrade;

					placed = true;
				}
			}

			// Incrementa l'id poichè ho generato un oggetto
			currentId++;
		}

		// Altrimenti, eventualmente genera una AICar
		else if (r < obstacleCumulative + upgradeCumulative + AIcarProbability) {
			AICar* aicar = new AICar(Point2D(roadPosition + i, -3), AIDamage);

			// Velocità di scorrimento minore di quella della strada, e movimento orizzontale casuale
			aicar->velocity.y = this->speed * 0.5f;
			aicar->velocity.x = (rand() % 6) * ((i <= roadWidth / 2) ? 1.0f : -1.0f);

			// Numero casuale al centro dello sprite
			aicar->sprite[1][1].character = '0' + rand() % 10;

			// Colore casuale per bordi e numero al centro
			Color centerColor = (Color)(rand() % 15 + 1);
			Color borderColor = (Color)(rand() % 15 + 1);
			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {
					if (x == 1 && y == 1) {
						aicar->sprite[x][y].foreground = centerColor;
					}
					else {
						aicar->sprite[x][y].foreground = borderColor;
					}
				}
			}

			i += aicar->rect.size.width - 1;

			// Se non esce dalla strada, aggiungila alla scena
			if (i < roadWidth)
				scene->addGameObject(aicar);
			else
				delete aicar;
		}
	}
}