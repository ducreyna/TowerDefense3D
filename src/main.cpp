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

using namespace std;

OBJECT landscape;
Scene *scene;
double myObsParam[16];

/**
 * Function initializing the OpenGL window
 */
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.0, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20,20,10,0,0,0,0,0,1) ;
    glGetDoublev(GL_MODELVIEW_MATRIX, myObsParam);

    /* Set the background color: RGB mode */
    glClearColor(0.8,0.8,0.8,1);
    
    /* Apply background color and erase z-buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);	// Z-buffer activation
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
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
}


int main(int argc, char **argv)
{
	// Scene creation
	scene = new Scene();

    // Loading the static environnement
	landscape.type = 0;
    landscape.obj = new objLoader();
    landscape.obj->load((char *) "terrain_lo12.obj");

	scene->addObject(landscape);
    
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     // RGB mode
    
    glutCreateWindow("Tower Defense 3D");
    
    // Display the scene
    glutDisplayFunc(drawScene);

    // Reshape the scene
    glutReshapeFunc(reshape);
    
    // Keyboard functions
    //glutSpecialFunc(special_key_press); // Functions for the special keys of the keyboard
    //glutKeyboardFunc(key_press);		  // Functions for the alphanumeric keys
    
    // Mouse functions
    //glutMouseFunc(mouse_press);		  // Mouse buttons
    //glutMotionFunc(mouse_move);		  // Mouse moves
    
    init();
    glutMainLoop();

	return 0;
}
