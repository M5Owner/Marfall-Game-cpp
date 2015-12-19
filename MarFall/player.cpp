
#include "player.h"
#include "map.h"
#include "input.h"


using namespace std;
using namespace sf;


//Constructeur

Player::Player()
{
	// le spritesheet de Marfall zin del 3alaaam
	if (!marfallTexture.loadFromFile("graphics/marfall.png"))
	{
		cout << "Erreur durant le chargement du spritesheet de Marfall." << endl;
	}
	else
		marfall.setTexture(marfallTexture);

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

	life = 3;

	invincibleTimer = 0;

	direction = RIGHT;
	etat = IDLE;

	frameNumber = 0;

	frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;


	frameMax = 8;

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

	if (newLevel == true)
	{
		map.setStartX(map.getBeginX());
		map.setStartY(map.getBeginY());
	}

	w = PLAYER_WIDTH;
	h = PLAYER_HEIGTH;

	timerMort = 0;
	onGround = false;

}


void Player::draw(Map &map, RenderWindow &window)
{
	if (frameTimer <= 0)
	{
		frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;

		frameNumber++;

		if (frameNumber >= frameMax)
			frameNumber = 0;

	}
	else
		frameTimer--;


	marfall.setPosition(Vector2f(x - map.getStartX(), y - map.getStartY()));



	if (invincibleTimer > 0)
	{

		if (frameNumber % 2 == 0)
		{
			if (direction == LEFT)
			{

				marfall.setTextureRect(sf::IntRect(
					(frameNumber + 1) * w,
					etat * h,
					-w, h));
				window.draw(marfall);
			}
			else
			{
				marfall.setTextureRect(sf::IntRect(
					frameNumber * w,
					etat * h,
					w, h));
				window.draw(marfall);
			}
		}

	}


	else
	{
		if (direction == LEFT)
		{
			marfall.setTextureRect(sf::IntRect(
				(frameNumber + 1) * w,
				etat * h,
				-w, h));
			window.draw(marfall);
		}
		else
		{
			marfall.setTextureRect(sf::IntRect(
				frameNumber * w,
				etat * h,
				w, h));
			window.draw(marfall);
		}
	}

}



void Player::update(Input &input, Map &map)
{


	if (timerMort == 0)
	{
		if (invincibleTimer > 0)
			invincibleTimer--;


		dirX = 0;

		dirY += GRAVITY_SPEED;


		if (dirY >= MAX_FALL_SPEED)
			dirY = MAX_FALL_SPEED;



		if (input.getButton().left == true)
		{
			dirX -= PLAYER_SPEED;

			direction = LEFT;


			if (etat != WALK && onGround == true)
			{
				etat = WALK;
				frameNumber = 0;
				frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}
		}

		else if (input.getButton().right == true)
		{
			dirX += PLAYER_SPEED;
			direction = RIGHT;


			if (etat != WALK && onGround == true)
			{
				etat = WALK;
				frameNumber = 0;
				frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}
		}

		else if (input.getButton().right == false && input.getButton().left == false && onGround == true)
		{
			if (etat != IDLE)
			{
				etat = IDLE;
				frameNumber = 0;
				frameTimer = TIME_BETWEEN_2_FRAMES_PLAYER;
				frameMax = 8;
			}

		}



		if (input.getButton().up == true)
		{
			if (onGround == true)
			{
				dirY = -JUMP_HEIGHT;
				onGround = false;
				Playerjump = true;
			}
			else if (Playerjump == true)
			{
				dirY = -JUMP_HEIGHT;
				Playerjump = false;
			}
			input.setButton(jump, false);
		}


		if (onGround == true)
			Playerjump = true;


		if (onGround == false)
		{
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

		centerScrolling(map);

	}


	if (timerMort > 0)
	{
		timerMort--;

		if (timerMort == 0)
		{
			vies--;

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

	else if (cxperso < xlimmin)
	{
		map.setStartX(map.getStartX() - 4);
	}


	if (cxperso > map.getStartX() + SCREEN_WIDTH)
	{
		map.setStartX(map.getStartX() + 30);
	}

	else if (cxperso > xlimmax)
	{
		map.setStartX(map.getStartX() + 4);
	}

	if (map.getStartX() < 0)
	{
		map.setStartX(0);
	}


	else if (map.getStartX() + SCREEN_WIDTH >= map.getMaxX())
	{
		map.setStartX(map.getMaxX() - SCREEN_WIDTH);
	}

	if (cyperso < ylimmin)
	{
		map.setStartY(map.getStartY() - 4);
	}

	if (cyperso > ylimmax)
	{
		if (dirY >= MAX_FALL_SPEED - 2)
		{
			map.setStartY(map.getStartY() + MAX_FALL_SPEED + 1);
		}
		else
		{
			map.setStartY(map.getStartY() + 4);
		}
	}

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


	for (;;)
	{
		x1 = (x + dirX) / TILE_SIZE;
		x2 = (x + dirX + w - 1) / TILE_SIZE;


		y1 = (y) / TILE_SIZE;
		y2 = (y + i - 1) / TILE_SIZE;


		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (dirX > 0)
			{
				if (map.getTile(y1, x2) > BLANK_TILE || map.getTile(y2, x2) > BLANK_TILE)
				{


					x = x2 * TILE_SIZE;
					x -= w + 1;
					dirX = 0;

				}
			}

			else if (dirX < 0)
			{
				if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y2, x1) > BLANK_TILE)
				{
					x = (x1 + 1) * TILE_SIZE;
					dirX = 0;
				}

			}

		}

		if (i == h)
		{
			break;
		}

		i += TILE_SIZE;

		if (i > h)
		{
			i = h;
		}
	}


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
					y = y2 * TILE_SIZE;
					y -= h;
					dirY = 0;
					onGround = 1;
				}

			}

			else if (dirY < 0)
			{
				if (map.getTile(y1, x1) > BLANK_TILE || map.getTile(y1, x2) > BLANK_TILE)
				{
					y = (y1 + 1) * TILE_SIZE;
					dirY = 0;
				}

			}
		}

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

	checkSlope(map);

	x += dirX;
	y += dirY;

	if (x < 0)
	{
		x = 0;
	}

	else if (x + w >= map.getMaxX())
	{
		x = map.getMaxX() - w - 1;
	}

	if (y > map.getMaxY())
	{
		timerMort = 60;
	}
}



Player::Point Player::segment2segment(int Ax0, int Ay0, int Bx0, int By0, int Cx0, int Cy0, int Dx0, int Dy0)
{



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


	s1.x = tx*TILE_SIZE;
	s1.y = (ty + 1)*TILE_SIZE - cy;
	s2.x = (tx + 1)*TILE_SIZE;
	s2.y = (ty + 1)*TILE_SIZE - dy;
}


int Player::slopeEquation(int pente, double *a, double *b)
{

	const double xLeft = 0;
	const double xRight = 32.0;
	int yLeft, yRight;


	if (pente == TILE_PENTE_26_BenH_1)
	{
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

	double cd = (yRight - yLeft) / (xRight - xLeft); 
	double oo = yLeft - cd * 0; 
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

	if (wasOnGround == 0)
	{
		wasOnSlope = 0;
	}

	int posIniX = posXmem + w / 2;
	int xa = posIniX / TILE_SIZE;
	int posIniY = posYmem + h - 1;
	int ya = posIniY / TILE_SIZE;

	int posEndX = posIniX + dirXmem;
	int xb = posEndX / TILE_SIZE;
	int posEndY = posIniY + 1 + dirYmem;
	int yb = posEndY / TILE_SIZE;

	if (map.getTile(ya, xa) >= TILE_PENTE_26_BenH_1 && map.getTile(ya, xa) <= TILE_PENTE_26_HenB_2)
	{
		isOnSlope = map.getTile(ya, xa);
	}

	if (map.getTile(yb, xb) >= TILE_PENTE_26_BenH_1 && map.getTile(yb, xb) <= TILE_PENTE_26_HenB_2)
	{
		goOnSlope = map.getTile(yb, xb);
	}

	if (map.getTile(yb - 1, xb) >= TILE_PENTE_26_BenH_1 && map.getTile(yb - 1, xb) <= TILE_PENTE_26_HenB_2)
	{
		goOnSlopeUp = map.getTile(yb - 1, xb);
	}


	else if (map.getTile(yb + 1, xb) >= TILE_PENTE_26_BenH_1 && map.getTile(yb + 1, xb) <= TILE_PENTE_26_HenB_2)
	{
		goOnSlopeDown = map.getTile(yb + 1, xb);
	}

	if (goOnSlope > 0)
	{
		double a, b;

		if (!slopeEquation(goOnSlope, &a, &b)){ return 0; }

		int xPos = posEndX - xb*TILE_SIZE;

		int yPos = a * xPos + b;

		if (yPos > 31) { yPos = 31; }

		diagOffSet = TILE_SIZE - yPos;

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

		yc = yb - 1;

		wasOnSlope = goOnSlopeUp;
		checkWasOnSlope = 0;
	}

	else if (isOnSlope > 0)
	{
		if (wasOnGround == 0)
		{


			Player::Point segmentD, segmentF;

			getSlopeSegment(xa, ya, isOnSlope, segmentD, segmentF);

			Player::Point point = segment2segment(posIniX, posIniY, posEndX, posEndY, segmentD.x, segmentD.y, segmentF.x, segmentF.y);

			if (point.x == -1)
			{

				x = posXmem;
				dirX = dirXmem;
				return 0;
			}

			else if (point.x < -1)
			{
				cout << "ERROR - segment2segment() - Sprite aux coordonnées négatives !\n" << endl;
				x = posXmem;
				dirX = dirXmem;
				return 0;
			}

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

		}

	}


	if (wasOnSlope > 0 && checkWasOnSlope)
	{
		if ((dirXmem > 0 && wasOnSlope == TILE_PENTE_26_BenH_2) ||
			(dirXmem < 0 && wasOnSlope == TILE_PENTE_26_HenB_1))
		{
			yc = ya;
		}

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

		x = posXmem;
		dirX = dirXmem;
		y = yc * TILE_SIZE + diagOffSet;
		y -= h;
		dirY = 0;
		onGround = 1;

		if (resetWasOnSlope)
		{
			wasOnSlope = 0;
		}

		return 1;
	}

	return 0;

}
