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

#include <stdio.h>
#include "objLoader.h"
#include "Scene.h"

using namespace std;

objLoader *landscape;
Scene *scene;
double myObsParam[16];
int i = 0;
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.0, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6,6,6,0,0,0,0,0,1) ;
    glGetDoublev(GL_MODELVIEW_MATRIX, myObsParam);

    /* mode RGB : choix de la couleur de fond */
    glClearColor(0.8,0.8,0.8,1);
    
    /* applique la couleur de fond et efface le z-buffer*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);	//active le test de profondeur pour eliminer les partie cachee
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
}

void drawScene()
{
	scene->drawScene();
}

void reshape(int w, int h)
{
	scene->reshape(w, h);
}

int main(int argc, char **argv)
{
	scene = new Scene();

    // Chargement de l'environnement statique
    landscape = new objLoader();
	landscape->load((char *) "models/cube2.obj");

	scene->addObject(landscape);
    
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);   /* taille de la fenetre ecran */
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     /* mode rgb */
    
    glutCreateWindow("Tower Defense 3D");
    
    // Affichage de la scene
    glutDisplayFunc(drawScene);

    // Fonction de rechargement de la scene
    glutReshapeFunc(reshape);
    
    // Gestion du clavier
    //glutSpecialFunc(special_key_press); //declare la fonction de gestion des touches speciales du clavier
    //glutKeyboardFunc(key_press);		//declare la fonction de gestion des touches alpha numÈriques du clavier
    
    // Gestion de la souris
    //glutMouseFunc(mouse_press);			//declare la fonction de gestion des boutons de la souris
    //glutMotionFunc(mouse_move);			//declare la fonction de gestion des des mouvements de la souris
    
    init();
    glutMainLoop();

	return 0;
}
