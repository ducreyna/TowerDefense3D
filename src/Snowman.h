/*
 * Snowman.h
 *
 *  Created on: 24 déc. 2012
 *      Author: nathan
 */

#ifndef SNOWMAN_H_
#define SNOWMAN_H_

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
#include <ctime>
#include <cstdlib>
#include "ObjectStructure.h"

using namespace std;

class Snowman {
public:
	Snowman();
	virtual ~Snowman();
	/* Methods */
	void run();
	void inflictDamage(int damage);
	void increasePV();
	void decreasePV();

	/* Getters */
	OBJECT* getSnowman();
	GLdouble getPositionY();
	GLdouble getPositionX();

private:
	/* Attributes */
	OBJECT *snowM;
	double speed;
	int sens;
	bool headRotatedY;
	bool headRotatedX;
	int pv;
	int damages;

	/* Methods */
	void translate();
	bool translateX();
	void rotate(int sens);
	void reset();
	int myRandom();
};

#endif /* SNOWMAN_H_ */
