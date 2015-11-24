
#include "main.h"


int main(int argc, char *argv[])
{
	// Création d'une fenêtre en SFML 
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
		"Marfall jeu equipe Pentadev, GL_S5");

	//Limite les fps à 60 images / seconde
	window.setFramerateLimit(60);

	//On active la synchro verticale
	window.setVerticalSyncEnabled(true);

	//Instanciation des classes
	Input input;
	Map map;
	Player player;

	//On commence au premier niveau 
	map.setLevel(2);
	map.changeLevel();

	//On initialise le player
	player.initialize(map, true);
	player.setVies(3);
	player.setEtoiles(0);

	// Boucle infinie, principale, du jeu 
	while (window.isOpen())
	{
		/** GESTION DES INPUTS (CLAVIER) **/
		input.gestionInputs(window);

		/**  MISES A JOUR - UPDATES  **/
		//On met à jour le player
		player.update(input, map);

		/**  DESSIN **/
		//On dessine tout
		window.clear();

		//On affiche le background
		map.drawBackground(window);

		// Affiche la map de tiles : layer 2 (couche du fond) 
		map.draw(2, window);

		// Affiche la map de tiles : layer 1 (couche active : sol, etc.)
		map.draw(1, window);

		// Affiche le joueur 
		player.draw(map, window);

		// Affiche la map de tiles : layer 3 (couche en foreground / devant) 
		map.draw(3, window);

		window.display();
	}

	// On quitte
	return 0;

}



