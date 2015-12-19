
#include "main.h"


int main(int argc, char *argv[])
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Marfall jeu equipe Pentadev, GL_S5");
	

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	//Instanciation des classes
	Input input;
	Map map;
	Player player;

	map.setLevel(1);
	map.changeLevel();

	player.initialize(map, true);
	player.setVies(3);
	player.setEtoiles(0);

	// Boucle infinie, principale, du jeu 
	while (window.isOpen())
	{
		

		// GESTION DES INPUTS
		input.gestionInputs(window);

		player.update(input, map);

		window.clear();
		
		map.drawBackground(window);

		map.draw(2, window);

		map.draw(1, window);

		// Affiche le joueur 
		player.draw(map, window);

		map.draw(3, window);

		window.display();
	}

	return 0;

}



