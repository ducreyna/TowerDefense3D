/*
 * scene.cpp
 *
 *  Created on: 2 dŽc. 2012
 *      Author: nathan
 */

#include "scene.h"

Scene::Scene()
{
	this->lights = new Lighting();
}

Scene::~Scene() {}

/**
 * Method for drawing the scene
 */
void Scene::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);			// Erase the screen
	glClear(GL_DEPTH_BUFFER_BIT);			// Erase the z-buffer

	// Transmit all objects in the scene for lighting treatment
	this->lights->setObjects(this->objects);

	this->lights->defineSources();

	for(unsigned int i = 0; i < this->objects.size(); i++)
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
void Scene::drawObject(OBJECT object)
{
	for(int i = 0; i < object.obj->faceCount; i++)
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
void Scene::drawFace(OBJECT object, int indexFace)
{
	int j;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_POLYGON);
	// TODO definir les normales
	GLdouble A[3];
	j = object.obj->faceList[indexFace]->normal_index[0];
	A[0] = object.obj->normalList[j]->e[0];
	A[1] = object.obj->normalList[j]->e[1];
	A[2] = object.obj->normalList[j]->e[2];
	glNormal3dv(A);

	// Couleur verte
		glColor3d(0, 1, 0);

	// Material definition
	if(object.obj->faceList[indexFace]->material_index != -1)
		this->lights->defineMaterials(object.obj->faceList[indexFace]->material_index);

	for(int i = 0; i < object.obj->faceList[indexFace]->vertex_count; i++)
	{
		j = object.obj->faceList[indexFace]->vertex_index[i];
		glVertex3d(object.obj->vertexList[j]->e[0], object.obj->vertexList[j]->e[1], object.obj->vertexList[j]->e[2]);
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
void Scene::addObject(OBJECT object)
{
	this->objects.push_back(object);
}

/**
 * Public method for removing an object in the scene
 * @param The object to remove
 */
void Scene::removeObject(OBJECT object)
{
	bool found = false;
	for (unsigned int i = 0; !found && i < this->objects.size(); ++i)
	{
		if (this->objects[i].obj == object.obj)
		{
			this->objects[i] = this->objects[this->objects.size() -1];
			this->objects.pop_back();
			found = true;
			free(object.obj);
		}
	}
}

/**
 * Getter for objects list
 */
vector<OBJECT> Scene::getObjects()
{
	return this->objects;
}

