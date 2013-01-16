/*
 * Interactions.h
 *
 *  Created on: 17 déc. 2012
 *      Author: nathan
 */

#ifndef INTERACTIONS_H_
#define INTERACTIONS_H_

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
#include "Scene.h"

class Interactions {
public:
	Interactions(Scene *scene, int width, int height);
	virtual ~Interactions();

	/* Public Methods */
	void keyPressed(unsigned char key);
	void specialKeyPressed(int key);
	void mousePressed(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void setWindowSize(int width, int height);

private:
	/* Private attributes */
	Scene *scene;
	int width;
	int height;
	int curX;
	int curY;
};

#endif /* INTERACTIONS_H_ */
