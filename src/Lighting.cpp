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
	LIGHT_SOURCE main;
	main.id = 0;
	main.ambiant.r = 0.7;
	main.ambiant.g = 0.7;
	main.ambiant.b = 0.7;
	main.color.r = 1;
	main.color.g = 1;
	main.color.b = 1;
	main.position.x = 0;
	main.position.y = 0;
	main.position.z = 30;
	main.position.w = 1;
	main.allure_faisceau.k = 1;
	main.allure_faisceau.theta = 180;
	main.direction.x = 0;
	main.direction.y = 0;
	main.direction.z = -1;
	main.direction.w = 1;
	main.on = 0;
	
	LIGHT_SOURCE departure;
	departure.id = 1;
	departure.ambiant.r = 0.7;
	departure.ambiant.g = 0.7;
	departure.ambiant.b = 0.7;
	/*departure.color.r = 0.17;
	departure.color.g = 0.46;*/
		departure.color.r = 0;
		departure.color.g = 0;
	departure.color.b = 1;
	departure.position.x = 0;
	departure.position.y = -32.5;
	//departure.position.y = -33;
	departure.position.z = 5;
	departure.position.w = 1;
	departure.allure_faisceau.k = 1;
	departure.allure_faisceau.theta = 40;
	departure.direction.x = 0;
	departure.direction.y = 0.5;
	departure.direction.z = -1;
	departure.direction.w = 1;
	departure.on = 1;

	LIGHT_SOURCE arrival;
	arrival.id = 1;
	arrival.ambiant.r = 0.33;
	arrival.ambiant.g = 0.98;
	arrival.ambiant.b = 0.55;
	/*arrival.color.r = 0.33;
	arrival.color.g = 0.98;
	arrival.color.b = 0.55;*/
		arrival.color.r = 0;
		arrival.color.g = 1;
		arrival.color.b = 0;
	arrival.position.x = 0;
	arrival.position.y = 23;
	arrival.position.z = 5;
	arrival.position.w = 1;
	arrival.allure_faisceau.k = 1;
	arrival.allure_faisceau.theta = 40;
	arrival.direction.x = 0;
	arrival.direction.y = -0.5;
	arrival.direction.z = -1;
	arrival.direction.w = 1;
	arrival.on = 1;

	LIGHT_SOURCE tower;
	tower.id = 1;
	tower.ambiant.r = 1;
	tower.ambiant.g = 0;
	tower.ambiant.b = 0;
	tower.color.r = 1;
	tower.color.g = 0;
	tower.color.b = 0;
	tower.position.x = 0;
	//tower.position.y = -11.6;
	tower.position.y = 0;
	tower.position.z = 10;
	tower.position.w = 1;
	tower.allure_faisceau.k = 1;
	tower.allure_faisceau.theta = 18;
	tower.direction.x = 0;
	tower.direction.y = -1;
	tower.direction.z = -1;
//		tower.direction.x = 0;
//		tower.direction.y = 0;
//		tower.direction.z = -1;
	tower.direction.w = 1;
	tower.on = 1;

	this->lightSources.push_back(main);
	this->lightSources.push_back(departure);
	this->lightSources.push_back(arrival);
	this->lightSources.push_back(tower);

	this->curAngle = (-pi*90)/180;
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
 * @return w GLdouble[3]* Coordinates x, y, z
 */
GLdouble* Lighting::vectorProduct(GLdouble u[3], GLdouble v[3])
{
	GLdouble *w = (GLdouble*)malloc(3 * sizeof(GLdouble));;
	w[0]= u[1]*v[2] - u[2]*v[1];
	w[1]= u[2]*v[0] - u[0]*v[2];
	w[2]= u[0]*v[1] - u[1]*v[0];

	return w;
}

void Lighting::defineMaterials(int indexObject, int indexMaterial)
{
	// r->amb[0] g->amb[1] b->amb[2]
	GLfloat vect[4];

	vect[0] = this->objects[indexObject]->obj->materialList[indexMaterial]->amb[0];
	vect[1] = this->objects[indexObject]->obj->materialList[indexMaterial]->amb[1];
	vect[2] = this->objects[indexObject]->obj->materialList[indexMaterial]->amb[2];
	vect[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, vect);

	vect[0] = this->objects[indexObject]->obj->materialList[indexMaterial]->diff[0];
	vect[1] = this->objects[indexObject]->obj->materialList[indexMaterial]->diff[1];
	vect[2] = this->objects[indexObject]->obj->materialList[indexMaterial]->diff[2];
	vect[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, vect);

	vect[0] = this->objects[indexObject]->obj->materialList[indexMaterial]->spec[0];
	vect[1] = this->objects[indexObject]->obj->materialList[indexMaterial]->spec[1];
	vect[2] = this->objects[indexObject]->obj->materialList[indexMaterial]->spec[2];
	vect[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, vect);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->objects[indexObject]->obj->materialList[indexMaterial]->shiny);

	/*vect[0]=0;
	vect[1]=0;
	vect[2]=0;
	vect[3]=1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, vect);*/
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
	//glDisable(GL_COLOR_MATERIAL);
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
//			quadObj = gluNewQuadric();
//			glDisable(GL_LIGHTING);
			//glColor3d(this->lightSources[i].color.r, this->lightSources[i].color.g, this->lightSources[i].color.b);
//			glPushMatrix();
//			glTranslatef(this->lightSources[i].position.x, this->lightSources[i].position.y, this->lightSources[i].position.z);
//			gluSphere(quadObj, 0.1, 10, 10);
//			glEnable(GL_LIGHTING);
//			glPopMatrix();
		}
		else
			glDisable(source);
	}
//	glEnable(GL_COLOR_MATERIAL);
//	glColorMaterial(GL_FRONT, GL_DIFFUSE);
//	glColorMaterial(GL_FRONT, GL_AMBIENT);
//	glColorMaterial(GL_FRONT, GL_SPECULAR);
}

/*
 * Public method to switch between global lighting and spots
 */
void Lighting::switchLighting()
{
	if(this->lightSources[0].id == 0 || this->lightSources[0].id == 5)
	{
		if(this->lightSources[0].on == 1)
		{
			for(unsigned int i = 1; i < this->lightSources.size(); i++)
			{
				this->lightSources[i].on = 1;
			}
			this->lightSources[0].on = 0;
		}
		else
		{
			for(unsigned int i = 1; i < this->lightSources.size(); i++)
			{
				this->lightSources[i].on = 0;
			}
			this->lightSources[0].on = 1;
		}
	}
	else
	{
		if(this->lightSources[0].on == 1)
		{
			for(unsigned int i = 1; i < this->lightSources.size(); i++)
			{
				if(this->lightSources[i].id == 1)
				{
					this->lightSources[i].on = 0;
				}
				else
				{
					this->lightSources[i].on = 1;
				}
			}
			this->lightSources[0].on = 0;
		}
		else
		{
			for(unsigned int i = 1; i < this->lightSources.size(); i++)
			{
				if(this->lightSources[i].id == 1)
				{
					this->lightSources[i].on = 1;
				}
				else
				{
					this->lightSources[i].on = 0;
				}
			}
			this->lightSources[0].on = 1;
		}
	}
}

/**
 * Public method to rotate the spot on the tower
 * @param angle
 * @param centerX
 * @param centerY
 * @param centerZ
 */
void Lighting::rotateSpotTower(double angle, double centerX, double centerY, double centerZ)
{
	this->lightSources[3].direction.x = centerX / 33.5;
	this->lightSources[3].direction.y = centerY / 33.5;

	/*this->lightSources[3].position.x = 11.6 * cos(this->curAngle + (pi*angle)/180);
	this->lightSources[3].position.y = 11.6 * sin(this->curAngle + (pi*angle)/180);

	this->curAngle += (pi*angle)/180;*/
}

/**
 * Setter for the vector of objects
 * @param objects Vector of objects in the scene
 */
void Lighting::setObjects(vector<OBJECT*> objects)
{
	this->objects = objects;
}
