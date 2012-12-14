/*
 * scene.h
 *
 *  Created on: 2 d�c. 2012
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
#include "objLoader.h"

#include "Lighting.h"

using namespace std;

class Scene {
public:
	Scene();
	virtual ~Scene();

	/* Public methods */
	void drawScene();
	void reshape(int width, int height);
	void addObject(objLoader *object);
	void removeObject(objLoader *object);
	/* Getters */
	vector<objLoader*> getObjects();

private:
	/* Private attributes*/
	vector<objLoader*> objects;
	Lighting *lights;

	/* Private methods */
	void drawObject(objLoader* object);
	void drawFace(objLoader *object, int indexFace);
	void drawRepere();
};

#endif /* SCENE_H_ */
