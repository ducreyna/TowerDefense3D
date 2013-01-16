/*
 * Lighting.h
 *
 *  Created on: 6 déc. 2012
 *      Author: nathan
 */

#ifndef LIGHTING_H_
#define LIGHTING_H_

#if defined(__APPLE__) && defined(__MACH__)
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "LightStruture.h"
#include "ObjectStructure.h"
#include <iostream>
#include <cmath>
#include <vector>

#define pi 3.14159265

using namespace std;

class Lighting {
public:
	Lighting();
	Lighting(vector<objLoader> *objects);
	virtual ~Lighting();

	/* Methods */
	void defineMaterials(int indexObject, int indexMaterial);
	void defineSources();
	void switchLighting();
	void rotateSpotTower(double angle, double centerX, double centerY, double centerZ);
	/* Setters */
	void setObjects(vector<OBJECT*> objects);
	GLdouble* vectorProduct(GLdouble u[3], GLdouble v[3]);
private:
	/* Attributes */
	vector<OBJECT*> objects;
	vector<LIGHT_SOURCE> lightSources;
	double curAngle;

	/* Methods */
	GLdouble norm(GLdouble v[3]);

	GLenum ligth_i(int i);
};

#endif /* LIGHTING_H_ */
