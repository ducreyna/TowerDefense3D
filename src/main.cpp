//============================================================================
// Name        : TowerDefense.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
#include <string>
#include <stdio.h>
#include "ObjectStructure.h"
#include "Scene.h"
#include "Interactions.h"

using namespace std;

Scene *scene;
Interactions *interactions;

/**
 * Function initializing the OpenGL window
 */
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.0, 0.1, 100);
    
	// Set up mouse and keys interactions
    interactions = new Interactions(scene, 700, 700);

    // Enable observers
    scene->enableObserver();

    /* Set the background color: RGB mode */
    glClearColor(0.8,0.8,0.8,1);
    
    /* Apply background color and erase z-buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);	// Z-buffer activation
    glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    // Antialiasing
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    // modele de gouraud
    glShadeModel(GL_SMOOTH);

    // Perspective and colors corrections
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

    // Texture
    glEnable(GL_TEXTURE_2D);
    scene->initTexture();
}


/**
 * Callback function for drawing the scene
 */
void drawScene()
{
	scene->drawScene();
}

/**
 * Callback function for reshaping the scene
 * @param w Integer representing the width
 * @param h Integer representing the height
 */
void reshape(int w, int h)
{
	scene->reshape(w, h);
	interactions->setWindowSize(w, h);
}

void keyPressed(unsigned char key, int x, int y)
{
	interactions->keyPressed(key);
}

void specialKeyPressed(int key, int x, int y)
{
	interactions->specialKeyPressed(key);
}

void mouseMoved(int x, int y)
{
	interactions->mouseMove(x, y);
}

void run()
{
	scene->runAnimations();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	// Creation of the scene
	scene = new Scene();

    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     // RGB mode

    glutCreateWindow("Tower Defense 3D");

    // Display the scene
    glutDisplayFunc(drawScene);

    // Reshape the scene
    glutReshapeFunc(reshape);

    // Keyboard functions
    glutSpecialFunc(specialKeyPressed); // Functions for the special keys of the keyboard
    glutKeyboardFunc(keyPressed);		  // Functions for the alphanumeric keys

    // Mouse functions
    glutPassiveMotionFunc(mouseMoved);		  // Mouse moves
    glutIdleFunc(run);

    init();
    glutMainLoop();

	return 0;
}
