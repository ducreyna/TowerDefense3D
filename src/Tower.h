/*
 * Tower.h
 *
 *  Created on: 21 déc. 2012
 *      Author: nathan
 */

#ifndef TOWER_H_
#define TOWER_H_

#if defined(__APPLE__) && defined(__MACH__)
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <iostream>
#include <vector.h>
#include "ObjectStructure.h"
#include "Snowman.h"
#include "Projectile.h"
#include "ParticuleStructure.h"

#define pi 3.14159265
#define MAX_PARTICLES 200

using namespace std;

class Tower {
public:
	Tower();
	virtual ~Tower();

	/* Methods */
	void rotationCannon(float angle);
	vector<Projectile*> attack(vector<Snowman*> snowmen, int nbSnowmenWave);
	void checkCollisions(vector<Snowman*> snowmen, int nbSnowmenWave);
	void dessinerParticules();
	void increasePower();
	void decreasePower();

	/* Getters */
	OBJECT* getObjCannon();

private:
	/* Attributes */
	OBJECT *cannon;
	int power;
	double targetArea;
	double damageArea;
	vector<Projectile*> cannonballs;
	int maxCannonballs;
	float curAngle;
	vector<PARTICLES*> particles;
	double speedXY;
	double speedZ;

	/* Methods */
	bool shoot(double snowmanX, double snowmanY);
	void removeProjectile(Projectile *projectile);
	double random(double min, double max);
	void addParticles(double x, double y);
};

#endif /* TOWER_H_ */
