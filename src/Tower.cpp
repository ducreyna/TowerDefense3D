/*
 * Tower.cpp
 *
 *  Created on: 21 déc. 2012
 *      Author: nathan
 */

#include "Tower.h"

Tower::Tower() {
	this->cannon = new OBJECT;

	this->cannon->type = 1;
	this->cannon->statique = false;
	this->cannon->obj = new objLoader();
    this->cannon->obj->load((char *) "tourelle.obj");
    //this->cannon.MTRANSFO = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
    this->cannon->MTRANSFO[0] = 1.0;
    this->cannon->MTRANSFO[1] = 0.0;
    this->cannon->MTRANSFO[2] = 0.0;
    this->cannon->MTRANSFO[3] = 0.0;
    this->cannon->MTRANSFO[4] = 0.0;
    this->cannon->MTRANSFO[5] = 1.0;
    this->cannon->MTRANSFO[6] = 0.0;
    this->cannon->MTRANSFO[7] = 0.0;
    this->cannon->MTRANSFO[8] = 0.0;
    this->cannon->MTRANSFO[9] = 0.0;
    this->cannon->MTRANSFO[10] = 1.0;
    this->cannon->MTRANSFO[11] = 0.0;
    this->cannon->MTRANSFO[12] = 0.0;
    this->cannon->MTRANSFO[13] = 0.0;
    this->cannon->MTRANSFO[14] = 0.0;
    this->cannon->MTRANSFO[15] = 1.0;

    this->power = 10;
    this->targetArea = 4;
    this->damageArea = 4;
    this->curAngle = (-pi*270)/180;
    this->speedXY = 70;
    this->speedZ = 30;

    this->maxCannonballs = 2;
    for(int i = 0; i < this->maxCannonballs; i++)
    {
    	this->cannonballs.push_back(new Projectile);
    }
}

Tower::~Tower() {}

/**
 * Method for the cannon rotation
 * @param angle The angle of rotation
 */
void Tower::rotationCannon(float angle)
{
	glMatrixMode(GL_MODELVIEW);		// Matrice product
	glPushMatrix();
	glLoadMatrixd(this->cannon->MTRANSFO); // Substituted by the transformation matrice corresponding

	// multiplied by the transformation matrix
	glRotatef(angle, 0, 0, 1);

	// retrieving the result as a new transformation matrix for the object
	glGetDoublev(GL_MODELVIEW_MATRIX, this->cannon->MTRANSFO);
	glPopMatrix();

	this->curAngle += (pi*angle)/180;
}

/**
 * Public method to know if a snowman is in the target area
 * @param snowmen A vector containing snowmen in the scene
 * @param nbSnowmenWave An integer representing the number of snowmen in the current wave
 * @return vector of projectiles
 */
vector<Projectile*> Tower::attack(vector<Snowman*> snowmen, int nbSnowmenWave)
{
	for(int i = 0; i < nbSnowmenWave; i++)
	{
		if(this->shoot(snowmen[i]->getPositionX(), snowmen[i]->getPositionY()))
		{
			for(unsigned int j = 0; j < this->cannonballs.size(); j++)
			{
				if(this->cannonballs[j]->getObjCannonball()->hide)
				{
					this->cannonballs[j]->go(this->curAngle);
					return this->cannonballs;
				}
			}
		}
	}
	return this->cannonballs;
}

/**
 * Private method to know if the tower can shoot
 * @param snowmanX X position of the snowman
 * @param snowmanY Y position of the snowman
 * @return bool True if the tower can shoot
 */
bool Tower::shoot(double snowmanX, double snowmanY)
{
	double x = 10.5 * cos(this->curAngle);
	double y = 12 * sin(this->curAngle);

	if(snowmanX < 0)
	{
		snowmanX *= -1;
		x *= -1;
	}

	if((snowmanX != 0 && abs(snowmanX - x) <= targetArea) && abs(snowmanY - y) <= targetArea)
	{
		bool shootOk = true;
		for(unsigned int i = 0; i < this->cannonballs.size(); i++)
		{
			if(!this->cannonballs[i]->getObjCannonball()->hide && this->cannonballs[i]->getPositionZ() > 3.5)
				shootOk = false;
		}
		if(shootOk)
			return true;
		else
			return false;
	}
	else
		return false;
}

/**
 * Public method to check if the projectile must explose
  * @param snowmen A vector containing snowmen in the scene
  * @param nbSnowmenWave An integer representing the number of snowmen in the current wave
 */
void Tower::checkCollisions(vector<Snowman*> snowmen, int nbSnowmenWave)
{
	for(unsigned int i = 0; i < this->cannonballs.size(); i++)
	{
		if(this->cannonballs[i]->getPositionZ() <= 0)
		{
			this->addParticles(this->cannonballs[i]->getPositionX(), this->cannonballs[i]->getPositionY());
			double x = 10.5 * cos(this->curAngle);
			double y = 12 * sin(this->curAngle);
			double snowmanX;
			double snowmanY;

			for(unsigned int j = 0; j < snowmen.size(); j++)
			{
				snowmanX = snowmen[j]->getPositionX();
				snowmanY = snowmen[j]->getPositionY();
				if(snowmanX < 0)
				{
					snowmanX *= -1;
					x *= -1;
				}

				if(abs(snowmanX - x) <= damageArea && abs(snowmanY - y) <= damageArea)
				{
					snowmen[j]->inflictDamage(this->power);
				}
			}
			this->cannonballs[i]->reset();
		}
	}
}

/**
 * Private method to generate an random number
 * @param min The limit minimum
 * @param max The limit maximum
 * @return double a random number
 */
double Tower::random(double min, double max)
{  return (double) (min + ((float) rand() / RAND_MAX * (max - min + 1.0)));
}

/**
 * Private method to add a new bloc of particles
 * @param x The X position of the particles bloc
 * @param y The Y position of the particles bloc
 */
void Tower::addParticles(double x, double y)
{
	particles.push_back((PARTICLES*)malloc(MAX_PARTICLES * sizeof(PARTICLES)));

	for(int i=0; i<MAX_PARTICLES; i++)
	{
		particles[particles.size()-1][i].x = x;
		particles[particles.size()-1][i].y = y;

		particles[particles.size()-1][i].active = true;
		particles[particles.size()-1][i].life = 1.0;

		particles[particles.size()-1][i].fade = random(0.01,0.05);   // Vitesse de disparition aléatoire

		particles[particles.size()-1][i].r = random(0.8,1.0);  // Quantité aléatoire de Rouge
		particles[particles.size()-1][i].g = random(0.0,0.33);  // Quantité aléatoire de Vert
		particles[particles.size()-1][i].b = 0;

		particles[particles.size()-1][i].xi = random(-this->speedXY, this->speedXY);   // Vitesse aléatoire
		particles[particles.size()-1][i].yi = random(-this->speedXY, this->speedXY);
		particles[particles.size()-1][i].zi = random(0.0, this->speedZ);

		particles[particles.size()-1][i].xg = 0.0;       // Gravité dirigée selon l'axe -Z
		particles[particles.size()-1][i].yg = 0.0;
		particles[particles.size()-1][i].zg = -1.0;
	}
}

/**
 * Public method to draw particles
 */
void Tower::dessinerParticules()
{
	for(unsigned int j = 0; j < this->particles.size(); j++)
	{
		for(int i=0; i<MAX_PARTICLES; i++)
		{
			if(particles[j][i].active && particles[j][i].z >= 0)
			{
				float x = particles[j][i].x;   // On récupère sa position
				float y = particles[j][i].y;
				float z = particles[j][i].z;



				glDisable(GL_LIGHTING);

				/* Dessin de carrés à partir de deux triangles (plus rapide pour la carte video */
				glBegin(GL_TRIANGLE_STRIP);
				/* Couleur de la particule; transparence = vie */
				glColor4d(particles[j][i].r, particles[j][i].g, particles[j][i].b, particles[j][i].life);
				  glVertex3d(x+0.1,y,z+0.1); // Nord-Ouest
				  glVertex3d(x-0.1,y,z+0.1); // Nord-Est
				  glVertex3d(x+0.1,y,z-0.1); // Sud-Ouest
				  glVertex3d(x-0.1,y,z-0.1); // Sud-Est
				glEnd();

				glEnable(GL_LIGHTING);
				/* Déplacement */
				particles[j][i].x += particles[j][i].xi/1000;
				particles[j][i].y += particles[j][i].yi/1000;
				particles[j][i].z += particles[j][i].zi/100;

				/* Gravité */
				particles[j][i].xi += particles[j][i].xg;
				particles[j][i].yi += particles[j][i].yg;
				particles[j][i].zi += particles[j][i].zg;

				/* "Vie" */
				particles[j][i].life -= particles[j][i].fade;

				/* Si la particule est "morte" on la régénère */
				/*if (particles[j][i].life < 0.0)
				{
					particles[j][i].life = 1.0;    // Maximum de vie
					particles[j][i].fade = myRand(0.01,0.05);

					particles[j][i].x = 0.0; // On renvoie la particule au centre
					particles[j][i].y = 0.0;
					particles[j][i].z = 0.0;

					particles[j][i].xi = myRand(-70.0,70.0);   // Vitesse aléatoire
					particles[j][i].yi = myRand(-70.0,70.0);
					particles[j][i].zi = myRand(0.0,100.0);

					particles[j][i].r=myRand(0.8,1.0);  // Quantité aléatoire de Rouge
					particles[j][i].g=myRand(0.0,0.33);  // Quantité aléatoire de Vert
					particles[j][i].b = 0;  // Quantité aléatoire de Bleu
				}*/
			}
		}
	}
}

/**
 * Public method to increase the power of the tower
 */
void Tower::increasePower()
{
	if(this->power < 30)
	{
		this->power += 2;
		this->speedXY += 2;
		this->speedZ += 0.5;
	}
}

/**
 * Public method to decrease the power of the tower
 */
void Tower::decreasePower()
{
	if(this->power > 10)
	{
		this->power -= 2;
		this->speedXY -= 2;
		this->speedZ -= 0.5;
	}
}

/**
 * Getter for the object file of the cannon
 * @return the object file
 */
OBJECT* Tower::getObjCannon()
{
	return this->cannon;
}
