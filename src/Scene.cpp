/*
 * scene.cpp
 *
 *  Created on: 2 déc. 2012
 *      Author: nathan
 */

#include "scene.h"

Scene::Scene() {}

Scene::~Scene() {}

/**
 * Method for drawing the scene
 */
void Scene::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);			// Erase the screen
	glClear(GL_DEPTH_BUFFER_BIT);			// Erase the z-buffer

	for(int i = 0; i < this->objects.size(); i++)
	{
		drawObject(this->objects[i]);
	}

	// Display the reference x y z
	drawRepere();

	glutSwapBuffers();		// switch active window and work window
}

/**
 * Method for drawing an object
 * @param *object The object to draw in the scene
 */
void Scene::drawObject(objLoader* object)
{
	for(int i = 0; i < object->faceCount; i++)
	{
		glPushMatrix();
		drawFace(object, i);
		glPopMatrix();
	}
}

/**
 * Method for drawing a face
 * @param *object The object that owns the face
 * @param indexFace The index of the face
 */
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
		//cout << "x: " << object->vertexList[j]->e[0]
		glVertex3d(object->vertexList[j]->e[0], object->vertexList[j]->e[2], object->vertexList[j]->e[1]);
	}

	glEnd();
}

/**
 * Method for drawing the 3D reference
 */
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

/**
 * Public method for reshaping the scene
 * @param width The new width of the scene
 * @param heigth The new height of the scene
 */
void Scene::reshape(int width, int height)
{
	if(height < 1) height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * Public method for adding an object in the scene
 * @param The object to add
 */
void Scene::addObject(objLoader *object)
{
	this->objects.push_back(object);
}

/**
 * Public method for removing an object in the scene
 * @param The object to remove
 */
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

