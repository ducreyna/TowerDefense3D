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

#include "objLoader.h"

class Scene {
public:
	Scene();
	Scene(objLoader* data);
	virtual ~Scene();

	void dessineScene();
	void reshape(int width, int height);

private:
	objLoader* data;

	void dessineFace(int indiceFace);
	void dessineRepere();
};

#endif /* SCENE_H_ */
