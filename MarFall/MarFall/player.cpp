
#include "player.h"
#include "map.h"
#include "input.h"


using namespace std;
using namespace sf;


//Constructeur

Player::Player()
{
	//Chargement de la spritesheet de Rabidja
	if (!rabidjaTexture.loadFromFile("graphics/rabidja.png"))
	{
		// Erreur
		cout << "Erreur durant le chargement du spritesheet de Rabidja." << endl;
	}
	else
		rabidja.setTexture(rabidjaTexture);

	//Initialisation des variables :
	dirX = 0;
	dirY = 0;
	life = 3;
	invincibleTimer = 0;
	x = y = h = w = 0;
	checkpointActif = false;
	respawnX = respawnY = 0;
	frameNumber = frameTimer = frameMax = 0;
	etat = direction = 0;
	timerMort = 0;
	onGround = false;
	dirX = dirY = 0;
	saveX = saveY = 0;
	Playerjump = false;

}


//Accesseurs
int Player::getX(void) const { return x; }
int Player::getY(void) const { return y; }
int Player::getW(void) const { return w; }
int Player::getH(void) const { return h; }
float Player::getDirX(void) const { return dirX; }
float Player::getDirY(void) const { return dirY; }
int Player::getOnGround(void) const { return onGround; }
int Player::getLife(void) const { return life; }
int Player::getVies(void) const { return vies; }
int Player::getEtoiles(void) const { return etoiles; }
int Player::getDirection(void) const { return direction; }


//Mutateurs
void Player::setX(int valeur) { x = valeur; }
void Player::setY(int valeur) { y = valeur; }
void Player::setW(int valeur) { w = valeur; }
void Player::setH(int valeur) { h = valeur; }
void Player::setDirX(float valeur) { dirX = valeur; }
void Player::setDirY(float valeur) { dirY = valeur; }
void Player::setOnGround(bool valeur) { onGround = valeur; }
void Player::setTimerMort(int valeur) { timerMort = valeur; }
void Player::setVies(int valeur) { vies = valeur; }
void Player::setEtoiles(int valeur) { etoiles = valeur; }
void Player::setCheckpoint(bool valeur) { checkpointActif = valeur; }


//Fonctions

void Player::initialize(Map &map, bool newLevel)
{
	//PV � 3
	life = 3;

	//Timer d'invincibilit� � 0
	invincibleTimer = 0;

	//Indique l'�tat et la direction de notre h�ros
	direction = RIGHT;
	etat = IDLE;

	//Indique le num�ro de la frame o� commencer
	frameNumber = 0;

	//...la valeur de son chrono ou timer
	frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

	
	frameMax = 8;

	/* Coordonn�es de d�marrage/respawn de notre h�ros */
	if (checkpointActif == true)
	{
		x = respawnX;
		y = respawnY;
	}
	else
	{
		x = map.getBeginX();
		y = map.getBeginY();
	}

	//On r�initiliase les coordonn�es de la cam�ra
	//si on change de niveau
	if (newLevel == true)
	{
		map.setStartX(map.getBeginX());
		map.setStartY(map.getBeginY());
	}

	/* Hauteur et largeur de notre h�ros */
	w = PLAYER_WIDTH;
	h = PLAYER_HEIGTH;

	//Variables n�cessaires au fonctionnement de la gestion des collisions
	timerMort = 0;
	onGround = false;

}


void Player::draw(Map &map, RenderWindow &window)
{
	/* Gestion du timer */
	// Si notre timer (un compte � rebours en fait) arrive � z�ro
	if (frameTimer <= 0)
	{
		//On le r�initialise
		frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

		//Et on incr�mente notre variable qui compte les frames de 1 pour passer � la suivante
		frameNumber++;

		//Mais si on d�passe la frame max, il faut revenir � la premi�re :
		if (frameNumber >= frameMax)
			frameNumber = 0;

	}
	//Sinon, on d�cr�mente notre timer
	else
		frameTimer--;


	//Ensuite, on peut passer la main � notre fonction
	rabidja.setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));

	

	//Si on a �t� touch� et qu'on est invincible
	if (invincibleTimer > 0)
	{
		//On fait clignoter le h�ros une frame sur deux
		
		if (frameNumber % 2 == 0)
		{
			//Gestion du flip 
			if (direction == LEFT)
			{
				
				rabidja.setTextureRect(sf::IntRect(
					(frameNumber + 1) * w,
					etat * h,
					-w, h));
				window.draw(rabidja);
			}
			else
			{
				rabidja.setTextureRect(sf::IntRect(
					frameNumber * w,
					etat * h,
					w, h));
				window.draw(rabidja);
			}
		}
		
	}

	
	else
	{
		//Gestion du flip (retournement de l'image selon que le sprite regarde � droite ou � gauche)
		if (direction == LEFT)
		{
			//On n'a plus de flip auto en SFML, il faut donc tout calculer
			rabidja.setTextureRect(sf::IntRect(
				(frameNumber + 1) * w,
				etat * h,
				-w, h));
			window.draw(rabidja);
		}
		else
		{
			rabidja.setTextureRect(sf::IntRect(
				frameNumber * w,
				etat * h,
				w, h));
			window.draw(rabidja);
		}
	}

}



void Player::update(Input &input, Map &map)
{
	
	//on r�initialise.
	
	if (timerMort == 0)
	{
		//On g�re le timer de l'invincibilit�
		if (invincibleTimer > 0)
			invincibleTimer--;

		
		dirX = 0;

		// La gravit� fait toujours tomber le perso : on incr�mente donc le vecteur Y
		dirY += GRAVITY_SPEED;

		
		if (dirY >= MAX_FALL_SPEED)
			dirY = MAX_FALL_SPEED;


		
		if (input.getButton().left == true)
		{
			dirX -= PLAYER_SPEED;
			
			direction = LEFT;

			
			if (etat != WALK && onGround == true)
			{
				//On enregistre l'anim' de la marche et on l'initialise � 0
				etat = WALK;
				frameNumber = 0;
				frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}
		}

		//Si on d�tecte un appui sur la touche fl�ch�e droite
		else if (input.getButton().right == true)
		{
			//On augmente les coordonn�es en x du joueur
			dirX += PLAYER_SPEED;
			//Et on indique qu'il va � droite (pour le flip
			//de l'affichage, rappelez-vous).
			direction = RIGHT;

			
			if (etat != WALK && onGround == true)
			{
				//On enregistre l'anim' de la marche et on l'initialise � 0
				etat = WALK;
				frameNumber = 0;
				frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}
		}

		//Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivit� (Idle)
		else if (input.getButton().right == false && input.getButton().left == false && onGround == true)
		{
			//On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
			//� chaque tour de boucle
			if (etat != IDLE)
			{
				//On enregistre l'anim' de l'inactivit� et on l'initialise � 0
				etat = IDLE;
				frameNumber = 0;
				frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}

		}


		
		if (input.getButton().up== true)
		{
			if (onGround == true)
			{
				dirY = -JUMP_HEIGHT;
				onGround = false;
				Playerjump = true;
			}
			// Si on est en saut 1, on peut faire un deuxi�me bond et on remet jump1 � 0 
			else if (Playerjump == true)
			{
				dirY = -JUMP_HEIGHT;
				Playerjump = false;
			}
			input.setButton(jump, false);
		}


		/* R�active la possibilit� de double saut si on tombe sans sauter */
		if (onGround == true)
			Playerjump = true;


		//On g�re l'anim du saut
		if (onGround == false)
		{
			//Si on est en saut 1, on met l'anim' du saut normal
			if (Playerjump == true)
			{
				if (etat != JUMP1)
				{
					etat = JUMP1;
					frameNumber = 0;
					frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
					frameMax = 2;
				}
			}
			else
			{
				if (etat != JUMP2)
				{
					etat = JUMP2;
					frameNumber = 0;
					frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
					frameMax = 4;
				}
			}
		}

		
		mapCollision(map);

		//On g�re le scrolling
		centerScrolling(map);

	}

	
	if (timerMort > 0)
	{
		timerMort--;

		if (timerMort == 0)
		{
			//On perd une vie
			vies--;

			// Si on est mort, on r�initialise le niveau
			map.changeLevel();
			initialize(map, false);
		}
	}
}


void Player::centerScrolling(Map &map)
{
	
	int cxperso = x + w / 2;
	int cyperso = y + h / 2;
	int xlimmin = map.getStartX() + LIMITE_X;
	int xlimmax = xlimmin + LIMITE_W;
	int ylimmin = map.getStartY() + LIMITE_Y;
	int ylimmax = ylimmin + LIMITE_H;

	
	if (cxperso < map.getStartX())
	{
		map.setStartX(map.getStartX() - 30);
	}

	//Si on d�passe par la gauche, on recule la cam�ra
	else if (cxperso < xlimmin)
	{
		map.setStartX(map.getStartX() - 4);
	}

	
	if (cxperso > map.getStartX() + SCREEN_WIDTH)
	{
		map.setStartX(map.getStartX() + 30);
	}

	//Si on d�passe par la droite, on avance la cam�ra
	else if (cxperso > xlimmax)
	{
		map.setStartX(map.getStartX() + 4);
	}

	//Si on arrive au bout de la map � gauche, on stoppe le scrolling
	if (map.getStartX() < 0)
	{
		map.setStartX(0);
	}

	
	else if (map.getStartX() + SCREEN_WIDTH >= map.getMaxX())
	{
		map.setStartX(map.getMaxX() - SCREEN_WIDTH);
	}

	//Si on d�passe par le haut, on remonte la cam�ra
	if (cyperso < ylimmin)
	{
		map.setStartY(map.getStartY() - 4);
	}

	//Si on d�passe par le bas, on descend la cam�ra
	if (cyperso > ylimmax)
	{
		//Sauf si on tombe tr�s vite, auquel cas, on acc�l�re la cam�ra :
		if (dirY >= MAX_FALL_SPEED - 2)
		{
			map.setStartY(map.getStartY() + MAX_FALL_SPEED + 1);
		}
		else
		{
			map.setStartY(map.getStartY() + 4);
		}
	}

	//Si on arrive au bout de la map en haut, on stoppe le scrolling
	if (map.getStartY() < 0)
	{
		map.setStartY(0);
	}

	
	else if (map.getStartY() + SCREEN_HEIGHT >= map.getMaxY())
	{
		map.setStartY(map.getMaxY() - SCREEN_HEIGHT);
	}

}


void Player::mapCollision(Map &map)
{

	int i, x1, x2, y1, y2;

	// R�cup des infos pour la gestion des pentes 
	dirXmem = dirX;
	wasOnGround = onGround;
	dirYmem = dirY;
	posXmem = x;
	posYmem = y;

	
	onGround = 0;

	

	if (h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = h;


	//On lance alors une boucle for infinie car on l'interrompra selon
	//les r�sultats de nos calculs
	for (;;)
	{
		//On va calculer ici les coins de notre sprite � gauche et �
		//droite pour voir quelle tile ils touchent.
		x1 = (x + dirX) / TILE_SIZE;
		x2 = (x + dirX + w - 1) / TILE_SIZE;

		
		y1 = (y) / TILE_SIZE;
		y2 = (y + i - 1) / TILE_SIZE;

		
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			//Si on a un mouvement � droite
			if (dirX > 0)
			{
				//On v�rifie si les tiles recouvertes sont solides
				if (map.getTile(y1, x2) > BLANK_TILE || map.getTile(y2, x2) > BLANK_TILE)
				{
					

					x = x2 * TILE_SIZE;
					x -= w + 1;
					dirX = 0;

				}
			}

			//M�me chose � gauche
			else if (dirX < 0)
			{
				if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y2, x1) > BLANK_TILE)
				{
					x = (x1 + 1) * TILE_SIZE;
					dirX = 0;
				}

			}

		}

		//On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
		if (i == h)
		{
			break;
		}

		//Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
		i += TILE_SIZE;

		if (i > h)
		{
			i = h;
		}
	}


	//On recommence la m�me chose avec le mouvement vertical (axe des Y)
	if (w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = w;


	for (;;)
	{
		x1 = (x) / TILE_SIZE;
		x2 = (x + i) / TILE_SIZE;

		y1 = (y + dirY) / TILE_SIZE;
		y2 = (y + dirY + h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (dirY > 0)
			{
				
				if (map.getTile(y2, x1) > TILE_TRAVERSABLE || map.getTile(y2, x2) > TILE_TRAVERSABLE)
				{
					//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
					//on le d�clare sur le sol (onGround).
					y = y2 * TILE_SIZE;
					y -= h;
					dirY = 0;
					onGround = 1;
				}

			}

			else if (dirY < 0)
			{
				// D�placement vers le haut 
				if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y1, x2) > BLANK_TILE)
				{
					y = (y1 + 1) * TILE_SIZE;
					dirY = 0;
				}

			}
		}

		//On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
		if (i == w)
		{
			break;
		}

		i += TILE_SIZE;

		if (i > w)
		{
			i = w;
		}
	}

	// Contr�le des pentes 
	checkSlope(map);

	/* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqu� */
	x += dirX;
	y += dirY;

	//Et on contraint son d�placement aux limites de l'�cran.
	if (x < 0)
	{
		x = 0;
	}

	else if (x + w >= map.getMaxX())
	{
		//Si on touche le bord droit de l'�cran, on annule
		//et on limite le d�placement du joueur
		x = map.getMaxX() - w - 1;
	}

	//Maintenant, s'il sort de l'�cran par le bas (chute dans un trou sans fond), on lance le timer
	//qui g�re sa mort et sa r�initialisation
	if (y > map.getMaxY())
	{
		timerMort = 60;
	}
}



Player::Point Player::segment2segment(int Ax0, int Ay0, int Bx0, int By0, int Cx0, int Cy0, int Dx0, int Dy0)
{
	

	// Cette fonciton permet de savoir si 2 segments se touchent
	// En param�tres, les coordonn�es des points du segment AB et du segment CD

	double Sx;
	double Sy;

	double Ax = Ax0;
	double Ay = Ay0;
	double Bx = Bx0;
	double By = By0;
	double Cx = Cx0;
	double Cy = Cy0;
	double Dx = Dx0;
	double Dy = Dy0;

	Player::Point point;
	point.x = -1;
	point.y = -1;

	if (Ax == Bx)
	{
		if (Cx == Dx)
			return point;
		else
		{
			double pCD = (Cy - Dy) / (Cx - Dx);
			Sx = Ax;
			Sy = pCD*(Ax - Cx) + Cy;
		}
	}
	else
	{
		if (Cx == Dx)
		{
			double pAB = (Ay - By) / (Ax - Bx);
			Sx = Cx;
			Sy = pAB*(Cx - Ax) + Ay;
		}
		else if ((Ax == Cx && Ay == Cy) || (Ax == Dx && Ay == Dy))
		{
			
			Sx = Ax;
			Sy = Ay;
		}
		else
		{
			double pCD = (Cy - Dy) / (Cx - Dx);
			double pAB = (Ay - By) / (Ax - Bx);
			double oCD = Cy - pCD*Cx;
			double oAB = Ay - pAB*Ax;
			Sx = (oAB - oCD) / (pCD - pAB);
			Sy = pCD*Sx + oCD;
		}
	}

	if ((Sx<Ax && Sx<Bx) | (Sx>Ax && Sx>Bx) | (Sx<Cx && Sx<Dx) | (Sx>Cx && Sx>Dx)
		| (Sy<Ay && Sy<By) | (Sy>Ay && Sy>By) | (Sy<Cy && Sy<Dy) | (Sy>Cy && Sy>Dy))
		return point;

	point.x = Sx;
	point.y = Sy;
	return point;
}


void Player::getSlopeSegment(int tx, int ty, int pente, Point &s1, Point &s2)
{
	

	int cy, dy;

	if (pente == TILE_PENTE_26_BenH_1)
	{
		cy = 0;
		dy = 16;
	}
	else if (pente == TILE_PENTE_26_BenH_2)
	{
		cy = 16;
		dy = 32;
	}
	else if (pente == TILE_PENTE_26_HenB_1)
	{
		cy = 32;
		dy = 16;
	}
	else if (pente == TILE_PENTE_26_HenB_2)
	{
		cy = 16;
		dy = 0;
	}
	else
	{
		cout << "### ERROR - getSlopeSegment() - Pente non connue ! ###" << endl;
	}


	// On ajoute la distance depuis le d�but/haut de la Map
	s1.x = tx*TILE_SIZE;
	s1.y = (ty + 1)*TILE_SIZE - cy;
	s2.x = (tx + 1)*TILE_SIZE;
	s2.y = (ty + 1)*TILE_SIZE - dy;
}


int Player::slopeEquation(int pente, double *a, double *b)
{
	//Adaptation de la fonction �crite par Stephantasy en SFML2

	const double xLeft = 0;
	const double xRight = 32.0;
	int yLeft, yRight;

	// On retourne son �quation de la pente
	// Diagonale � 26.5�

	if (pente == TILE_PENTE_26_BenH_1)
	{
		// D�but et fin de la pente dans la Tile (en Y)
		yLeft = 0;
		yRight = 16;
	}
	else if (pente == TILE_PENTE_26_BenH_2)
	{
		yLeft = 16;
		yRight = 32;
	}
	else if (pente == TILE_PENTE_26_HenB_1)
	{
		yLeft = 32;
		yRight = 16;
	}
	else if (pente == TILE_PENTE_26_HenB_2)
	{
		yLeft = 16;
		yRight = 0;
	}
	else
	{
		cout << "### ERROR - getSlopeSegment() - Pente non connue ! ###" << endl;
		return 0;
	}

	// On d�termine l'�quation
	double cd = (yRight - yLeft) / (xRight - xLeft); // Coefficient directeur
	double oo = yLeft - cd * 0; // Ordonn�e � l'origine
	*a = cd;
	*b = oo;

	return 1;
}


int Player::checkSlope(Map &map)
{
	
	// Initialisation
	int isOnSlope, goOnSlope, goOnSlopeUp, goOnSlopeDown;
	isOnSlope = goOnSlope = goOnSlopeUp = goOnSlopeDown = 0;
	int diagOffSet = 0;
	int yc;
	int resetWasOnSlope = 0, checkWasOnSlope = 1;

	// Si on ne touche plus le sol, on ne se soucis plus de savoir qu'on �tait sur une pente.
	if (wasOnGround == 0)
	{
		wasOnSlope = 0;
	}

	// On r�cup�re la position du Sprite (� noter qu'on effectue les tests avec le point "en bas au centre" du Sprite)
	int posIniX = posXmem + w / 2;
	int xa = posIniX / TILE_SIZE;
	int posIniY = posYmem + h - 1;
	int ya = posIniY / TILE_SIZE;

	// On r�cup�re la destination du Sprite
	int posEndX = posIniX + dirXmem;
	int xb = posEndX / TILE_SIZE;
	int posEndY = posIniY + 1 + dirYmem;
	int yb = posEndY / TILE_SIZE;

	// Est-ce qu'on est sur une pente ?
	if (map.getTile(ya, xa) >= TILE_PENTE_26_BenH_1 && map.getTile(ya, xa) <= TILE_PENTE_26_HenB_2)
	{
		isOnSlope = map.getTile(ya, xa);
	}

	// Est-ce qu'on va sur une pente ?
	if (map.getTile(yb, xb) >= TILE_PENTE_26_BenH_1 && map.getTile(yb, xb) <= TILE_PENTE_26_HenB_2)
	{
		goOnSlope = map.getTile(yb, xb);
	}

	// Est-ce que la Tile au-dessus de la destination du Sprite est une pente ?
	if (map.getTile(yb - 1, xb) >= TILE_PENTE_26_BenH_1 && map.getTile(yb - 1, xb) <= TILE_PENTE_26_HenB_2)
	{
		goOnSlopeUp = map.getTile(yb - 1, xb);
	}

	
	else if (map.getTile(yb + 1, xb) >= TILE_PENTE_26_BenH_1 && map.getTile(yb + 1, xb) <= TILE_PENTE_26_HenB_2)
	{
		goOnSlopeDown = map.getTile(yb + 1, xb);
	}

	// Si on se dirige vers une pente
	if (goOnSlope > 0)
	{
		double a, b;

		// On r�cup�re l'�quation de la pente
		if (!slopeEquation(goOnSlope, &a, &b)){ return 0; }

		// On determine la position en x du Sprite dans la Tile
		int xPos = posEndX - xb*TILE_SIZE;

		// On calcule sa position en y
		int yPos = a * xPos + b;

		// On borne le ypos � 31
		if (yPos > 31) { yPos = 31; }

		// On calcul l'Offset entre le haut de la Tile et le sol de la pente
		diagOffSet = TILE_SIZE - yPos;

		// La Tile "pente" est � la m�me hauteur que la Tile o� se trouve le Sprite
		yc = yb;

		
		wasOnSlope = goOnSlope;

		
		checkWasOnSlope = 0;
	}

	
	else if (goOnSlopeUp > 0)
	{
		double a, b;
		if (!slopeEquation(goOnSlopeUp, &a, &b)){ return 0; }
		int xPos = posEndX - xb*TILE_SIZE;
		int yPos = a * xPos + b;
		if (yPos > 31) { yPos = 31; }
		diagOffSet = TILE_SIZE - yPos;

		// La Tile "pente" est 1 Tile au-dessus de la Tile o� se trouve le Sprite
		yc = yb - 1;

		wasOnSlope = goOnSlopeUp;
		checkWasOnSlope = 0;
	}

	// Si on tombe ici, c'est que le Sprite ne va pas sur une pente mais qu'il est sur une pente.
	else if (isOnSlope > 0)
	{
		// Si on est en l'air,
		if (wasOnGround == 0)
		{

			
			Player::Point segmentD, segmentF;

			// On r�cup�re le segment de la pente
			getSlopeSegment(xa, ya, isOnSlope, segmentD, segmentF);

			// On r�cup�re la position du point de collision entre les segments (s'il y a lieu, sinon -1)
			Player::Point point = segment2segment(posIniX, posIniY, posEndX, posEndY, segmentD.x, segmentD.y, segmentF.x, segmentF.y);

			// Pas d'intersection
			if (point.x == -1)
			{
				
				x = posXmem;
				dirX = dirXmem;
				return 0;
			}

			else if (point.x < -1)
			{
				// Erreur dans la fonction "segment2segment()", on ne doit pas retourner de valeur < -1 !
				cout << "ERROR - segment2segment() - Sprite aux coordonn�es n�gatives !\n" << endl;
				x = posXmem;
				dirX = dirXmem;
				return 0;
			}

			// On positionne le Sprite
			x = point.x - w / 2;
			dirX = 0;
			y = point.y;
			y -= h;

			
			if (dirY > 0)
			{
				dirY = 0;
				onGround = 1;
			}

			wasOnSlope = isOnSlope;

			return 1;
		}

		
		else
		{

			if (goOnSlopeDown > 0)
			{
				double a, b;
				if (!slopeEquation(goOnSlopeDown, &a, &b)){ return 0; }
				int xPos = posEndX - xa*TILE_SIZE;

				
				if (dirXmem > 0)
				{
					xPos -= TILE_SIZE;
				}
				else
				{
					xPos += TILE_SIZE;
				}

				int yPos = a * xPos + b;
				if (yPos > 31) { yPos = 31; }
				diagOffSet = TILE_SIZE - yPos;
				yc = yb + 1;
				wasOnSlope = isOnSlope;
				checkWasOnSlope = 0;
			}

			// sinon on fait la transition en douceur avec "entity->wasOnSlope" ("checkWasOnSlope" restant � true)
		}

	}

	
	if (wasOnSlope > 0 && checkWasOnSlope)
	{
		// Si on quitte une mont�e
		if ((dirXmem > 0 && wasOnSlope == TILE_PENTE_26_BenH_2) ||
			(dirXmem < 0 && wasOnSlope == TILE_PENTE_26_HenB_1))
		{
			yc = ya;
		}

		// Si on quitte une descente
		else
		{
			if ((dirXmem > 0 && wasOnSlope == TILE_PENTE_26_HenB_2) ||
				(dirXmem < 0 && wasOnSlope == TILE_PENTE_26_BenH_1))
			{
				yc = ya + 1;
			}
		}

		resetWasOnSlope = 1;
	}

	//si on "quitte" une pente (donc que wasOnSlope > 0)
	if (wasOnSlope > 0)
	{
		
		if (wasOnGround == 0)
		{
			int newPos = yc * TILE_SIZE + diagOffSet;
			int ecart = newPos - posIniY;

			if (ecart > dirYmem)
			{
				y = posYmem;
				dirY = dirYmem;
				onGround = 0;
				return 0;
			}
		}

		// On positionne le Sprite sur la pente
		x = posXmem;
		dirX = dirXmem;
		y = yc * TILE_SIZE + diagOffSet;
		y -= h;
		dirY = 0;
		onGround = 1;

		// On n'oublie pas de remettre wasOnSlope � 0 si n�c�ssaire
		if (resetWasOnSlope)
		{
			wasOnSlope = 0;
		}

		return 1;
	}

	return 0;

}
