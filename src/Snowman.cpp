/*
 * Snowman.cpp
 *
 *  Created on: 24 dŽc. 2012
 *      Author: nathan
 */

#include "Snowman.h"

Snowman::Snowman() {
	this->snowM = new OBJECT;
	this->snowM->type = 2;
	this->snowM->statique = false;

	this->snowM->obj = new objLoader();
	this->snowM->obj->load((char *) "bonhomme_lo12.obj");
	this->snowM->hide = true;
	//this->snowM.MTRANSFO = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	this->snowM->MTRANSFO[0] = 1.0;
	this->snowM->MTRANSFO[1] = 0.0;
	this->snowM->MTRANSFO[2] = 0.0;
	this->snowM->MTRANSFO[3] = 0.0;
	this->snowM->MTRANSFO[4] = 0.0;
	this->snowM->MTRANSFO[5] = 1.0;
	this->snowM->MTRANSFO[6] = 0.0;
	this->snowM->MTRANSFO[7] = 0.0;
	this->snowM->MTRANSFO[8] = 0.0;
	this->snowM->MTRANSFO[9] = 0.0;
	this->snowM->MTRANSFO[10] = 1.0;
	this->snowM->MTRANSFO[11] = 0.0;
	this->snowM->MTRANSFO[12] = 0.0;
	this->snowM->MTRANSFO[13] = -33.0;
	this->snowM->MTRANSFO[14] = 0.0;
	this->snowM->MTRANSFO[15] = 1.0;

	srand(time(NULL));

	if(this->myRandom() > 0)
	{
		this->sens = 1;
	}
	else
	{
		this->sens = -1;
	}

	this->headRotatedY = false;
	this->headRotatedX = false;
	this->pv = 20;
	this->damages = 0;
	this->speed = 0.5;
}

Snowman::~Snowman() {}

/**
 * Public to run the translation of the snowman
 */
void Snowman::run()
{
	if(this->snowM->MTRANSFO[13] >= 22)
	{
		this->reset();
	}
	else
	{
		this->translate();
	}
}

/**
 * Private method to know if the snowman must translate on X
 */
bool Snowman::translateX()
{
	if(this->snowM->MTRANSFO[13] < 0)
	{
		if(this->snowM->MTRANSFO[12] < 0)
		{
			if(((this->snowM->MTRANSFO[13] * -1) - 12.9 < 0.1))
			{
				if(((this->snowM->MTRANSFO[12] * -1) - 10 > 0.1))
				{
					if(!this->headRotatedY)
					{
						this->rotate(-1);
						this->headRotatedY = true;
						this->headRotatedX = false;
					}
					return false;
				}
				else
				{
					// appliquer le random
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			if((this->snowM->MTRANSFO[13] * -1) - 12.9 < 0.1)
			{
				if((this->snowM->MTRANSFO[12] == 0) || (this->snowM->MTRANSFO[12] - 10 < 0.1))
				{
					// appliquer le random
					if(!this->headRotatedX)
					{
						this->rotate(this->sens*-1);
						this->headRotatedX = true;
						this->headRotatedY = false;
					}
					return true;
				}
				else
				{
					if(!this->headRotatedY)
					{
						this->rotate(1);
						this->headRotatedX = false;
						this->headRotatedY = true;
					}
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if(this->snowM->MTRANSFO[12] < 0)
		{
			if((this->snowM->MTRANSFO[13] - 10 > 0.1))
			{
				if(((this->snowM->MTRANSFO[12] > 0)))
				{
					return false;
				}
				else
				{
					if(!this->headRotatedX)
					{
						this->rotate(-1);
						this->headRotatedX = true;
						this->headRotatedY = false;
					}
					sens = 1;
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			if((this->snowM->MTRANSFO[13] - 10 > 0.1))
			{
				// source de probs
				if((this->snowM->MTRANSFO[12] > 0.5))
				{
					if(!this->headRotatedX)
					{
						this->rotate(1);
						this->headRotatedX = true;
						this->headRotatedY = false;
					}
					sens = -1;
					return true;
				}
				else
				{
					if(!this->headRotatedY)
					{
						this->rotate(this->sens);
						this->headRotatedY = true;
						this->headRotatedX = false;
					}
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
}

/**
 * Public method for the translation
 * @param x
 * @param y
 */
void Snowman::translate()
{
	if(translateX())
	{
		this->snowM->MTRANSFO[12] += sens * this->speed;
	}
	else
	{
		this->snowM->MTRANSFO[13] += this->speed;
	}
}

void Snowman::rotate(int sens)
{
	glMatrixMode(GL_MODELVIEW);		// Matrice product
	glPushMatrix();
	glLoadMatrixd(this->snowM->MTRANSFO); // Substituted by the transformation matrice corresponding

	// multiplied by the transformation matrix
	glRotatef(sens * 90, 0, 0, 1);

	// retrieving the result as a new transformation matrix for the object
	glGetDoublev(GL_MODELVIEW_MATRIX, this->snowM->MTRANSFO);
	glPopMatrix();
}

/**
 * Public method to inflict damage to the snowman
 * @param damage The number of points to decrease in pv
 */
void Snowman::inflictDamage(int damage)
{
	this->damages += damage;
	if((this->pv - this->damages) <= 0)
	{
		this->reset();
	}
}

/**
 * Private method to reset the snowman
 */
void Snowman::reset()
{
	this->snowM->hide = true;

	this->snowM->MTRANSFO[0] = 1.0;
	this->snowM->MTRANSFO[1] = 0.0;
	this->snowM->MTRANSFO[2] = 0.0;
	this->snowM->MTRANSFO[3] = 0.0;
	this->snowM->MTRANSFO[4] = 0.0;
	this->snowM->MTRANSFO[5] = 1.0;
	this->snowM->MTRANSFO[6] = 0.0;
	this->snowM->MTRANSFO[7] = 0.0;
	this->snowM->MTRANSFO[8] = 0.0;
	this->snowM->MTRANSFO[9] = 0.0;
	this->snowM->MTRANSFO[10] = 1.0;
	this->snowM->MTRANSFO[11] = 0.0;
	this->snowM->MTRANSFO[12] = 0.0;
	this->snowM->MTRANSFO[13] = -33.0;
	this->snowM->MTRANSFO[14] = 0.0;
	this->snowM->MTRANSFO[15] = 1.0;

	if(this->myRandom() > 0)
	{
		this->sens = 1;
	}
	else
	{
		this->sens = -1;
	}

	this->pv = 30;
	this->damages = 0;
	this->speed = 0.5;
}

/**
 * Private method to generate a random number
 */
int Snowman::myRandom()
{
	return (int)(random()/10e8);
}

/**
 * Public method to increase the pv of the snowman
 */
void Snowman::increasePV()
{
	//cout << this->pv << endl;
	if(this->pv < 90 && myRandom() == 0)
	{
		this->pv += 5;
		this->speed -= 0.025;

		glMatrixMode(GL_MODELVIEW);		// Matrice product
		glPushMatrix();
		glLoadMatrixd(this->snowM->MTRANSFO); // Substituted by the transformation matrice corresponding

		// multiplied by the transformation matrix
		glScaled(1.05,1.05,1.05);

		// retrieving the result as a new transformation matrix for the object
		glGetDoublev(GL_MODELVIEW_MATRIX, this->snowM->MTRANSFO);
		glPopMatrix();
	}
}

/**
 * Public method to decrease the pv of the snowman
 */
void Snowman::decreasePV()
{
	if(this->pv > 30 && myRandom() == 0)
	{
		this->pv -= 5;
		this->speed += 0.025;

		glMatrixMode(GL_MODELVIEW);		// Matrice product
		glPushMatrix();
		glLoadMatrixd(this->snowM->MTRANSFO); // Substituted by the transformation matrice corresponding

		// multiplied by the transformation matrix
		glScaled(0.95,0.95,0.95);

		// retrieving the result as a new transformation matrix for the object
		glGetDoublev(GL_MODELVIEW_MATRIX, this->snowM->MTRANSFO);
		glPopMatrix();
	}
}

/**
 * Getter for the snowman object
 * @return OBJECT the snowman
 */
OBJECT* Snowman::getSnowman()
{
	return this->snowM;
}

/**
 * Getter for the y position of the snowman
 * @param GLdouble the y position of the snowman
 */
GLdouble Snowman::getPositionY()
{
	return this->snowM->MTRANSFO[13];
}

/**
 * Getter for the x position of the snowman
 * @param GLdouble the x position of the snowman
 */
GLdouble Snowman::getPositionX()
{
	return this->snowM->MTRANSFO[12];
}
