/*
 * scene.cpp
 *
 *  Created on: 2 déc. 2012
 *      Author: nathan
 */

#include "scene.h"

Scene::Scene() {
}

Scene::~Scene() {}

void Scene::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);			//efface l'ecran
	glClear(GL_DEPTH_BUFFER_BIT);			//efface le buffer de profondeur

	for(int i = 0; i < this->objects.size(); i++)
	{
		drawObject(this->objects[i]);
	}

	// Affichage du repere
	drawRepere();

	glutSwapBuffers();						//echange la fenetre active et la fenetre de travail
}

void Scene::drawObject(objLoader* object)
{
	for(int i = 0; i < object->faceCount; i++)
	{
		glPushMatrix();
		drawFace(object, i);
		glPopMatrix();
	}
}

void Scene::drawFace(objLoader *object, int indexFace)
{
	int j;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);
	// TODO definir les normales
	// TODO definir les materiaux des lumieres

	for(int i = 0; i < object->faceList[indexFace]->vertex_count; i++)
	{
		j = object->faceList[indexFace]->vertex_index[i];
		glVertex3d(object->vertexList[j]->e[0], object->vertexList[j]->e[1], object->vertexList[j]->e[2]);
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

void Scene::addObject(objLoader *object)
{
	this->objects.push_back(object);
}

void Scene::removeObject(objLoader *object)
{
	bool found = false;
	for (unsigned int i = 0; !found && i < this->objects.size(); ++i)
	{
		if (this->objects[i] == object)
		{
			this->objects[i] = this->objects[this->objects.size() -1];
			this->objects.pop_back();
			found = true;
			free(object);
		}
	}
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

