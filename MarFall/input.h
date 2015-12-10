
#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>


class Input
{

	//Structures
	struct Button { bool left, right, up, down, jump, attack, enter; };

public:

	//Constructeur
	Input::Input();

	//Accesseur
	Button Input::getButton(void) const;

	//Mutateur
	void Input::setButton(int bouton, bool etat);

	//Fonctions
	void Input::gestionInputs(sf::RenderWindow &window);
	void Input::getInput(sf::RenderWindow &window);


private:

	//Variables de la classe en acc�s priv�
	sf::Event event;
	Button button;

	//Enum pour les boutons
	const enum{ up, down, right, left, attack, jump, enter };

};
#endif