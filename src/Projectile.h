/*
 * Projectile.h
 *
 *  Created on: 27 déc. 2012
 *      Author: nathan
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

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
#include <cmath>
#include "ObjectStructure.h"

using namespace std;

class Projectile {
public:
	Projectile();
	virtual ~Projectile();

	/* Methods */
	void run();
	void reset();
	void go(float angle);

	/* Getters */
	OBJECT* getObjCannonball();
	double getPositionX();
	double getPositionY();
	double getPositionZ();

private:
	/* Attributes */
	OBJECT *cannonball;
	double speed;
	float stepX;
	float stepY;

	/* Methods */
	void translate();
};

#endif /* PROJECTILE_H_ */
