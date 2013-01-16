/*
 * Projectile.cpp
 *
 *  Created on: 27 dŽc. 2012
 *      Author: nathan
 */

#include "Projectile.h"

Projectile::Projectile() {
	this->cannonball = new OBJECT;

	this->cannonball->type = 3;
	this->cannonball->statique = false;
	this->cannonball->hide = true;
	this->cannonball->obj = new objLoader();
	this->cannonball->obj->load((char *) "boulet.obj");
	//this->cannonball.MTRANSFO = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
	this->cannonball->MTRANSFO[0] = 1.0;
	this->cannonball->MTRANSFO[1] = 0.0;
	this->cannonball->MTRANSFO[2] = 0.0;
	this->cannonball->MTRANSFO[3] = 0.0;
	this->cannonball->MTRANSFO[4] = 0.0;
	this->cannonball->MTRANSFO[5] = 1.0;
	this->cannonball->MTRANSFO[6] = 0.0;
	this->cannonball->MTRANSFO[7] = 0.0;
	this->cannonball->MTRANSFO[8] = 0.0;
	this->cannonball->MTRANSFO[9] = 0.0;
	this->cannonball->MTRANSFO[10] = 1.0;
	this->cannonball->MTRANSFO[11] = 0.0;
	this->cannonball->MTRANSFO[12] = 0.0;
	this->cannonball->MTRANSFO[13] = -1.0;
	this->cannonball->MTRANSFO[14] = 7.0;
	this->cannonball->MTRANSFO[15] = 1.0;

	this->speed = 2;

	this->stepX = 0;
	this->stepY = 0;
}

Projectile::~Projectile() {}


void Projectile::run()
{
	this->translate();
}

void Projectile::translate()
{
	this->cannonball->MTRANSFO[12] += this->speed * this->stepX;
	this->cannonball->MTRANSFO[13] += this->speed * this->stepY;
	this->cannonball->MTRANSFO[14] -= this->speed * 0.7;
}

void Projectile::reset()
{
	this->cannonball->hide = true;
	this->cannonball->MTRANSFO[0] = 1.0;
	this->cannonball->MTRANSFO[1] = 0.0;
	this->cannonball->MTRANSFO[2] = 0.0;
	this->cannonball->MTRANSFO[3] = 0.0;
	this->cannonball->MTRANSFO[4] = 0.0;
	this->cannonball->MTRANSFO[5] = 1.0;
	this->cannonball->MTRANSFO[6] = 0.0;
	this->cannonball->MTRANSFO[7] = 0.0;
	this->cannonball->MTRANSFO[8] = 0.0;
	this->cannonball->MTRANSFO[9] = 0.0;
	this->cannonball->MTRANSFO[10] = 1.0;
	this->cannonball->MTRANSFO[11] = 0.0;
	this->cannonball->MTRANSFO[12] = 0.0;
	this->cannonball->MTRANSFO[13] = -1.0;
	this->cannonball->MTRANSFO[14] = 7.0;
	this->cannonball->MTRANSFO[15] = 1.0;

	this->speed = 0.8;
}

void Projectile::go(float angle)
{
	this->cannonball->hide = false;
	this->stepX = cos(angle);
	this->stepY = sin(angle);
}

/**
 * Getter for the object cannonball
 * @return OBJECT* structure
 */
OBJECT* Projectile::getObjCannonball()
{
	return this->cannonball;
}

/**
 * Getter for the X position of the projectile
 * @return X position
 */
double Projectile::getPositionX()
{
	return this->cannonball->MTRANSFO[12];
}

/**
 * Getter for the Y position of the projectile
 * @return Y position
 */
double Projectile::getPositionY()
{
	return this->cannonball->MTRANSFO[13];
}

/**
 * Getter for the Z position of the projectile
 * @return Z position
 */
double Projectile::getPositionZ()
{
	return this->cannonball->MTRANSFO[14];
}

