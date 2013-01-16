/*
 * scene.h
 *
 *  Created on: 2 déc. 2012
 *      Author: nathan
 */

#ifndef SCENE_H_
#define SCENE_H_

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
#include <vector>
#include <iterator>
#include <string.h>
#include <cmath>
#include "ObjectStructure.h"
#include "objLoader.h"
#include "Lighting.h"
#include "Observer.h"
#include "Tower.h"
#include "Snowman.h"
#include "Projectile.h"
#include "PngLoader.h"
#include "ParticuleStructure.h"

#define MAX_PARTICLES 1000
using namespace std;

class Scene {
public:
	Scene();
	virtual ~Scene();

	/* Public methods */
	void drawScene();
	void reshape(int width, int height);
	void addObject(OBJECT *object);
	void removeObject(OBJECT *object);
	void runAnimations();
	void launchWave(int nbSnowmen);
	void enableObserver();

	void initTexture();

	/* Getters */
	vector<OBJECT*> getObjects();
	Tower* getTower();
	Lighting* getLighting();
	Observer* getObserver();
	vector<Snowman*> getSnowmen();

private:
	/* Private attributes*/
	vector<OBJECT*> objects;
	Lighting *lights;
	Observer *observer;
	// Landscape
	OBJECT *landscape;
	// Tower
	Tower *tower;
	bool defaultRotationCannon;
	// Snowmen
	vector<Snowman*> snowmen;
	int nbSnowmen;
	// Projectiles
	vector<Projectile*> cannonballs;
	// Textures
	PngLoader loaderTex;
	GLuint currentTexture;
	GLuint *tabTextures;
	// Snow
	PARTICLES particle[MAX_PARTICLES];

	/* Private methods */
	void drawObject(int indexObject);
	void drawFace(int indexObject, int indexFace);
	void drawRepere();
	double random(double min, double max);
	void initSnow();
	void drawSnow();
	int getIndexTexture(char *filename);
	void drawSkybox(double *vect);
};


#endif /* SCENE_H_ */
