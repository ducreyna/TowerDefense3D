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
#include "ObjectStructure.h"
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
	void addObject(OBJECT object);
	void removeObject(OBJECT object);
	/* Getters */
	vector<OBJECT> getObjects();

private:
	/* Private attributes*/
	vector<OBJECT> objects;
	Lighting *lights;

	/* Private methods */
	void drawObject(OBJECT object);
	void drawFace(OBJECT object, int indexFace);
	void drawRepere();
};

#endif /* SCENE_H_ */
