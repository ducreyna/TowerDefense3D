/*
 * Lighting.cpp
 *
 *  Created on: 6 dŽc. 2012
 *      Author: nathan
 */

#include "Lighting.h"

Lighting::Lighting()
{
	// Lights declaration: Tower
	LIGHT_SOURCE source;
	source.ambiant.r = 0.2;
	source.ambiant.g = 0.2;
	source.ambiant.b = 0.2;
	source.color.r = 1;
	source.color.g = 1;
	source.color.b = 1;
	source.position.x = 0;
	source.position.y = 0;
	source.position.z = 10;
	source.position.w = 1;
	source.allure_faisceau.k = 1;
	source.allure_faisceau.theta = 40;
	source.direction.x = 0;
	source.direction.y = 0;
	source.direction.z = -1;
	source.direction.w = 1;
	source.on = 1;

	this->lightSources.push_back(source);
}

Lighting::~Lighting() {}

/**
 * Private method to calculate the norm of a vector
 * @param v GLdouble[3] Coordinates x, y, z
 */
GLdouble Lighting::norm(GLdouble v[3])
{
	GLdouble n;
	n = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	return(n);
}

/**
 * Private method to calculate a vector product
 * @param u GLdouble[3] Coordinates x, y, z
 * @param v GLdouble[3] Coordinates x, y, z
 * @param w GLdouble[3]* Coordinates x, y, z
 */
GLdouble* Lighting::vectorProduct(GLdouble u[3], GLdouble v[3])
{
	GLdouble *w = (GLdouble*)malloc(3 * sizeof(GLdouble));;
	w[0]= u[1]*v[2] - u[2]*v[1];
	w[1]= u[2]*v[0] - u[0]*v[2];
	w[2]= u[0]*v[1] - u[1]*v[0];

	return w;
}

void Lighting::defineMaterials(int indexMaterial)
{
	unsigned int i;
	// r->amb[0] g->amb[1] b->amb[2]
	GLfloat vect[4];

	for(i = 0; i < this->objects.size(); i++)
	{
		vect[0] = this->objects[i]->materialList[indexMaterial]->amb[0];
		vect[1] = this->objects[i]->materialList[indexMaterial]->amb[1];
		vect[2] = this->objects[i]->materialList[indexMaterial]->amb[2];
		vect[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vect);

		vect[0] = this->objects[i]->materialList[indexMaterial]->diff[0];
		vect[1] = this->objects[i]->materialList[indexMaterial]->diff[1];
		vect[2] = this->objects[i]->materialList[indexMaterial]->diff[2];
		vect[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vect);

		vect[0] = this->objects[i]->materialList[indexMaterial]->spec[0];
		vect[1] = this->objects[i]->materialList[indexMaterial]->spec[1];
		vect[2] = this->objects[i]->materialList[indexMaterial]->spec[2];
		vect[3] = 1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vect);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->objects[i]->materialList[indexMaterial]->shiny);

		/*vect[0]=scene->tabmat[i].emission.r;
		vect[1]=scene->tabmat[i].emission.g;
		vect[2]=scene->tabmat[i].emission.b;
		vect[3]=1.0;
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, vect);*/
	}
}

GLenum Lighting::ligth_i(int i)
{
	GLenum source;
	switch (i)
	{
	case 0:
		source=GL_LIGHT0;
		break;
	case 1:
		source=GL_LIGHT1;
		break;
	case 2:
		source=GL_LIGHT2;
		break;
	case 3:
		source=GL_LIGHT3;
		break;
	case 4:
		source=GL_LIGHT4;
		break;
	case 5:
		source=GL_LIGHT5;
		break;
	case 6:
		source=GL_LIGHT6;
		break;
	case 7:
		source=GL_LIGHT7;
		break;
	}

	if (i<=7)
		return(source);
	else
	{
		std::cout << ("Attention: nombre de sources lumineuses depasse\n") << std::endl;
		return ((GLenum)GL_LIGHT7);
	}
}

 /**
  * Public method to define light sources
  */
void Lighting::defineSources()
{
	/* source index */
	GLenum source;
	unsigned int i;
	GLfloat vect[4];
	GLUquadricObj *quadObj;
	glEnable(GL_LIGHTING);

	for(i = 0; i < this->lightSources.size(); i++)
	{
		source = this->ligth_i(i);

		if(this->lightSources[i].on)
		{
			vect[0] = this->lightSources[i].ambiant.r;
			vect[1] = this->lightSources[i].ambiant.g;
			vect[2] = this->lightSources[i].ambiant.b;
			vect[3] = 1.0;
			glLightfv(source,GL_AMBIENT,vect);

			vect[0] = this->lightSources[i].color.r;
			vect[1] = this->lightSources[i].color.g;
			vect[2] = this->lightSources[i].color.b;
			vect[3] = 1.0;
			glLightfv(source,GL_DIFFUSE,vect);
			glLightfv(source,GL_SPECULAR,vect);

			vect[0] = this->lightSources[i].position.x;
			vect[1] = this->lightSources[i].position.y;
			vect[2] = this->lightSources[i].position.z;
			vect[3] = this->lightSources[i].position.w;
			glLightfv(source,GL_POSITION,vect);

			vect[0] = this->lightSources[i].direction.x;
			vect[1] = this->lightSources[i].direction.y;
			vect[2] = this->lightSources[i].direction.z;
			vect[3] = this->lightSources[i].direction.w;
			glLightfv(source,GL_SPOT_DIRECTION,vect);

			glLightf(source,GL_SPOT_CUTOFF, this->lightSources[i].allure_faisceau.theta);
			glLightf(source,GL_SPOT_EXPONENT, this->lightSources[i].allure_faisceau.k);

			glEnable(source);

			//afficher une sphere à la position de chaque source
			quadObj = gluNewQuadric();
			glDisable(GL_LIGHTING);
			glColor3d(this->lightSources[i].color.r, this->lightSources[i].color.g, this->lightSources[i].color.b);
			glPushMatrix();
			glTranslatef(this->lightSources[i].position.x, this->lightSources[i].position.y, this->lightSources[i].position.z);
			gluSphere(quadObj, 0.1, 10, 10);
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}
		else
			glDisable(source);
	}
}

/**
 * Setter for the vector of objects
 * @param objects Vector of objects in the scene
 */
void Lighting::setObjects(vector<objLoader*> objects)
{
	this->objects = objects;
}
