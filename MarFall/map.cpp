
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

	//Chargement des 2 tilesets n�1
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


	/* Dessine la carte en commen�ant par startX et startY */

	
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
		//Deuxi�me couche de tiles ;)
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
		//Troisi�me couche de tiles ;)
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
	//On cr�e un flux (stream) pour lire notre fichier
	
	fstream fin;
	int x = 0;
	int y = 0;

	
	maxX = 0;
	maxY = 0;

	//On cr�e un vecteur en 2 dimensions 
	vector < vector < int > > lignes;

	//On cr�e un vecteur temporaire pour lire une ligne
	vector < int > myVectData;

	//On cr�e des cha�nes de caract�res temporaires
	string strBuf, strTmp;

	//On cr�e un stringstream pour g�rer nos cha�nes
	stringstream iostr;

	//On ouvre le fichier
	fin.open(filename, fstream::in);

	
	if (!fin.is_open())
	{
		cerr << "Erreur de chargement du fichier.\n";
		exit(1);
	}

	//On lit notre fichier jusqu'� la fin 
	while (!fin.eof())
	{
		//On r�cup�re la ligne dans la cha�ne strBuf
		getline(fin, strBuf);
		//Si la ligne est vide, on continue la boucle
		if (!strBuf.size())
			continue;

		//Sinon on poursuit et on r�initialise notre stringstream
		iostr.clear();

		//On y envoie le contenu du buffer strBuf
		iostr.str(strBuf);

		//On r�initialise le vecteur ligne
		myVectData.clear();

		//On boucle pour lire chaque num�ro de tile du fichier map
		while (true)
		{
			//Pour chaque ligne on r�cup�re le num�ro de la tile, en
			//les parsant gr�ce aux espaces qui les s�parent (' ')
			getline(iostr, strTmp, ' ');

			//On r�cup�re ce num�ro dans dans notre vecteur ligne
			myVectData.push_back(atoi(strTmp.c_str()));

			//Si on a fini, on quitte la boucle
			if (!iostr.good()) break;
		}

		//Si le vecteur ligne n'est pas vide, on l'envoie dans notre vecteur � 2 dimensions
		if (myVectData.size())
			lignes.push_back(myVectData);
	}

	//On ferme le fichier
	fin.close();

	
	beginx = lignes[0][0];

	beginy = lignes[0][1];

	tilesetAffiche = lignes[0][2];

	//On charge ensuite la premi�re ligne individuellement car elle contient + de donn�es
	//(d�calage de 3 num�ros � cause des 3 pr�c�dents)
	for (x = 3; x < MAX_MAP_X + 3; x++)
	{
		tile[y][x - 3] = lignes[y][x];
	}

	
	for (y = 1; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			//On copie la valeur de notre vecteur temporaire
			//dans notre tableau � deux dimensions
			tile[y][x] = lignes[y][x];

			//On d�tecte si la tile n'est pas vide
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

	//On fait la m�me chose pour la seconde couche de tiles :
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			tile2[y][x] = lignes[y + MAX_MAP_Y][x];
		}
	}

	//Puis pour la troisi�me :
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