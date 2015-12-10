
#include "map.h"

using namespace std;
using namespace sf;

//Constructeur
Map::Map()
{
	//Chargement des ressources graphiques
	//Chargement du background
	if (!backgroundTexture.loadFromFile("graphics/background.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image de background." << endl;
	}
	else
		background.setTexture(backgroundTexture);

	//Chargement des 2 tilesets n°1
	if (!tileSet1Texture.loadFromFile("graphics/tileset1.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image du tileset 1." << endl;
	}
	else
		tileSet1.setTexture(tileSet1Texture);

	if (!tileSet1BTexture.loadFromFile("graphics/tileset1b.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement de l'image du tileset 1b." << endl;
	}
	else
		tileSet1B.setTexture(tileSet1BTexture);


	//Autres variables
	mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	tileSetNumber = 0;
	level = 1;
	startX = startY = 0;
}


//Accesseurs
int Map::getBeginX(void) const { return beginx; }
int Map::getBeginY(void) const { return beginy; }
int Map::getStartX(void) const { return startX; }
int Map::getStartY(void) const { return startY; }
int Map::getMaxX(void) const { return maxX; }
int Map::getMaxY(void) const { return maxY; }
int Map::getTile(int y, int x) const { return tile[y][x]; }
int Map::getLevel(void) const { return level; }


//Mutateurs
void Map::setLevel(int valeur) { level = valeur; }
void Map::setStartX(int valeur) { startX = valeur; }
void Map::setStartY(int valeur) { startY = valeur; }
void Map::setTile(int y, int x, int valeur) { tile[y][x] = valeur; }


//Fonctions

void Map::changeLevel(void)
{
	string filename;
	filename = "map/map" + to_string(level) + ".txt";
	loadMap(filename);
}


void Map::drawBackground(RenderWindow &window)
{
	window.draw(background);
}


void Map::draw(int layer, RenderWindow &window)
{
	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

	
	mapX = startX / TILE_SIZE;

	
	x1 = (startX % TILE_SIZE) * -1;

	
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	/* On fait exactement pareil pour calculer y */
	mapY = startY / TILE_SIZE;
	y1 = (startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


	//On met en place un timer pour animer la map (chapitre 19)
	if (mapTimer <= 0)
	{
		if (tileSetNumber == 0)
		{
			tileSetNumber = 1;
			mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}
		else
		{
			tileSetNumber = 0;
			mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}

	}
	else
		mapTimer--;


	/* Dessine la carte en commençant par startX et startY */

	
	if (layer == 1)
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			
			mapX = startX / TILE_SIZE;

			
			for (x = x1; x < x2; x += TILE_SIZE)
			{

				
				a = tile[mapY][mapX];

				
				ysource = a / 10 * TILE_SIZE;
				
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (tileSetNumber == 0)
				{
					tileSet1.setPosition(Vector2f(x, y));
					tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
					window.draw(tileSet1);
				}
				else
				{
					tileSet1B.setPosition(Vector2f(x, y));
					tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
					window.draw(tileSet1B);
				}

				mapX++;
			}

			mapY++;
		}
	}

	else if (layer == 2)
	{
		//Deuxième couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE)
			{

				
				a = tile2[mapY][mapX];

				
				ysource = a / 10 * TILE_SIZE;
				
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (tileSetNumber == 0)
				{
					tileSet1.setPosition(Vector2f(x, y));
					tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
					window.draw(tileSet1);
				}
				else
				{
					tileSet1B.setPosition(Vector2f(x, y));
					tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
					window.draw(tileSet1B);
				}

				mapX++;
			}

			mapY++;
		}
	}

	else if (layer == 3)
	{
		//Troisième couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE)
			{

				
				a = tile3[mapY][mapX];

				
				ysource = a / 10 * TILE_SIZE;
				
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (tileSetNumber == 0)
				{
					tileSet1.setPosition(Vector2f(x, y));
					tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
					window.draw(tileSet1);
				}
				else
				{
					tileSet1B.setPosition(Vector2f(x, y));
					tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
					window.draw(tileSet1B);
				}

				mapX++;
			}

			mapY++;
		}
	}


}



void Map::testDefilement(void)
{
	
	if (startX < maxX - SCREEN_WIDTH)
		
		startX += 10;
}



void Map::loadMap(string filename)
{
	//On crée un flux (stream) pour lire notre fichier
	
	fstream fin;
	int x = 0;
	int y = 0;

	
	maxX = 0;
	maxY = 0;

	//On crée un vecteur en 2 dimensions 
	vector < vector < int > > lignes;

	//On crée un vecteur temporaire pour lire une ligne
	vector < int > myVectData;

	//On crée des chaînes de caractères temporaires
	string strBuf, strTmp;

	//On crée un stringstream pour gérer nos chaînes
	stringstream iostr;

	//On ouvre le fichier
	fin.open(filename, fstream::in);

	
	if (!fin.is_open())
	{
		cerr << "Erreur de chargement du fichier.\n";
		exit(1);
	}

	//On lit notre fichier jusqu'à la fin 
	while (!fin.eof())
	{
		//On récupère la ligne dans la chaîne strBuf
		getline(fin, strBuf);
		//Si la ligne est vide, on continue la boucle
		if (!strBuf.size())
			continue;

		//Sinon on poursuit et on réinitialise notre stringstream
		iostr.clear();

		//On y envoie le contenu du buffer strBuf
		iostr.str(strBuf);

		//On réinitialise le vecteur ligne
		myVectData.clear();

		//On boucle pour lire chaque numéro de tile du fichier map
		while (true)
		{
			//Pour chaque ligne on récupère le numéro de la tile, en
			//les parsant grâce aux espaces qui les séparent (' ')
			getline(iostr, strTmp, ' ');

			//On récupère ce numéro dans dans notre vecteur ligne
			myVectData.push_back(atoi(strTmp.c_str()));

			//Si on a fini, on quitte la boucle
			if (!iostr.good()) break;
		}

		//Si le vecteur ligne n'est pas vide, on l'envoie dans notre vecteur à 2 dimensions
		if (myVectData.size())
			lignes.push_back(myVectData);
	}

	//On ferme le fichier
	fin.close();

	
	beginx = lignes[0][0];

	beginy = lignes[0][1];

	tilesetAffiche = lignes[0][2];

	//On charge ensuite la première ligne individuellement car elle contient + de données
	//(décalage de 3 numéros à cause des 3 précédents)
	for (x = 3; x < MAX_MAP_X + 3; x++)
	{
		tile[y][x - 3] = lignes[y][x];
	}

	
	for (y = 1; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			//On copie la valeur de notre vecteur temporaire
			//dans notre tableau à deux dimensions
			tile[y][x] = lignes[y][x];

			//On détecte si la tile n'est pas vide
			if (tile[y][x] > 0)
			{
				//Si c'est la cas, on augmente la valeur de maxX ou
				//maxY car la map n'est pas encore finie.
				if (x > maxX)
				{
					maxX = x;
				}

				if (y > maxY)
				{
					maxY = y;
				}
			}
		}
	}

	//On fait la même chose pour la seconde couche de tiles :
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			tile2[y][x] = lignes[y + MAX_MAP_Y][x];
		}
	}

	//Puis pour la troisième :
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			tile3[y][x] = lignes[y + MAX_MAP_Y * 2][x];
		}
	}

	//On convertit les dimensions max de notre map en pixels
	maxX = (maxX + 1) * TILE_SIZE;
	maxY = (maxY + 1) * TILE_SIZE;
}