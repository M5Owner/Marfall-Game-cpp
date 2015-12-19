
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


class Map
{
public:

	//Constructeur
	Map::Map();

	//Accesseurs
	int Map::getBeginX(void) const;
	int Map::getBeginY(void) const;
	int Map::getStartX(void) const;
	int Map::getStartY(void) const;
	int Map::getMaxX(void) const;
	int Map::getMaxY(void) const;
	int Map::getTile(int y, int x) const;
	int Map::getLevel(void) const;

	//Mutateurs
	void Map::setLevel(int valeur);
	void Map::setStartX(int valeur);
	void Map::setStartY(int valeur);
	void Map::setTile(int y, int x, int valeur);

	//Fonctions
	void Map::drawBackground(sf::RenderWindow &window);
	void Map::loadMap(std::string filename);
	void Map::draw(int layer, sf::RenderWindow &window);
	void Map::changeLevel(void);
	void Map::testDefilement(void);


private:
	int tilesetAffiche;

	int beginx, beginy;
	int startX, startY;
	int maxX, maxY;

	/* Tableau à double dimension représentant la map de tiles */
	int tile[150][400];

	int tile2[150][400];

	int tile3[150][400];

	int mapTimer, tileSetNumber;

	int level;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite background;

	//Tilesets
	sf::Texture tileSet1Texture;
	sf::Sprite tileSet1;
	sf::Texture tileSet1BTexture;
	sf::Sprite tileSet1B;

	const int SCREEN_WIDTH = 800;
	const int  SCREEN_HEIGHT = 480;

	const int  MAX_MAP_X = 400;
	const int  MAX_MAP_Y = 150;

	const int  TILE_SIZE = 32;

	const int  TIME_BETWEEN_2_FRAMES = 20;


	const int BLANK_TILE = 99;


	const int TILE_TRAVERSABLE = 80;


	const int TILE_POWER_UP_DEBUT = 77;
	const int TILE_POWER_UP_FIN = 79;
	const int TILE_POWER_UP_COEUR = 78;


	const int TILE_RESSORT = 125;
	const int TILE_CHECKPOINT = 23;
	const int TILE_MONSTRE = 136;
	const int TILE_PIKES = 127;


	const int TILE_PLATEFORME_DEBUT = 130;
	const int TILE_PLATEFORME_FIN = 131;

	const int TILE_PENTE_26_BenH_1 = 69;
	const int TILE_PENTE_26_BenH_2 = 70;
	const int TILE_PENTE_26_HenB_1 = 71;
	const int TILE_PENTE_26_HenB_2 = 72;


};
#endif