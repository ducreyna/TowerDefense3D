/*
 * scene.cpp
 *
 *  Created on: 2 déc. 2012
 *      Author: nathan
 */

#include "scene.h"

Scene::Scene() {
}

Scene::Scene(objLoader* data):data(data){}

Scene::~Scene() {}

void Scene::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);			//efface l'ecran
	glClear(GL_DEPTH_BUFFER_BIT);			//efface le buffer de profondeur

	for(int i = 0; i < data->faceCount; i++)
	{
		glPushMatrix();
		drawFace(i);
		glPopMatrix();
	}

	// Affichage du repere
	drawRepere();

	glutSwapBuffers();						//echange la fenetre active et la fenetre de travail
}

void Scene::drawFace(int indiceFace)
{
	int j;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);
	// TODO definir les materiaux des lumieres

	for(int i = 0; i < data->faceList[indiceFace]->vertex_count; i++)
	{
		j = data->faceList[indiceFace]->vertex_index[i];
		glVertex3d(data->vertexList[j]->e[0], data->vertexList[j]->e[1], data->vertexList[j]->e[2]);
	}

	glEnd();
}

void Scene::drawRepere()
{
	int len=5;
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0); //red => x
		glVertex3d(0, 0, 0);
		glVertex3d(len, 0, 0);

		glColor3f(0.0, 1.0, 0.0); //green => y
		glVertex3d(0, 0, 0);
		glVertex3d(0, len, 0);

		glColor3f(0.0, 0.0, 1.0); //blue => z
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, len);

	glEnd();
	glEnable(GL_LIGHTING);
}

void Scene::reshape(int width, int height)
{
	if(height < 1) height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

