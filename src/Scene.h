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

#include "objLoader.h"

using namespace std;

class Scene {
public:
	Scene();
	virtual ~Scene();

	void drawScene();
	void reshape(int width, int height);
	void addObject(objLoader *object);
	void removeObject(objLoader *object);

private:
	vector<objLoader*> objects;

	void drawObject(objLoader* object);
	void drawFace(objLoader *object, int indexFace);
	void drawRepere();
};

#endif /* SCENE_H_ */
