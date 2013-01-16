/*
 * Observer.cpp
 *
 *  Created on: 16 dŽc. 2012
 *      Author: nathan
 */

#include "Observer.h"

Observer::Observer() {
	this->idObserver = 0;

	LOOKAT main;
	main.id = 0;
	main.type = 1;
	main.eyeX = 20;
	main.eyeY = 20;
	main.eyeZ = 10;
	main.centerX = 0;
	main.centerY = 0;
	main.centerZ = 0;
	main.upX = 0;
	main.upY = 0;
	main.upZ = 1;

	LOOKAT tower;
	tower.id = 1;
	tower.type = 0;
	tower.eyeX = 0.01;
	tower.eyeY = 0.01;
	tower.eyeZ = 9.3;
	tower.centerX = 0;
	tower.centerY = -33.5;
	tower.centerZ = 0;
	tower.upX = 0;
	tower.upY = 0;
	tower.upZ = 1;

	LOOKAT departure;
	departure.id = 2;
	departure.type = 0;
	departure.eyeX = 0;
	departure.eyeY = -33;
	departure.eyeZ = 4;
	departure.centerX = 0;
	departure.centerY = 0;
	departure.centerZ = 0;
	departure.upX = 0;
	departure.upY = 0;
	departure.upZ = 1;

	this->cameras.push_back(main);
	this->cameras.push_back(tower);
	this->cameras.push_back(departure);
}

Observer::~Observer() {}

/**
 * Public method to place the observer in the scene
 */
void Observer::placeObserver()
{
	for(unsigned int i = 0; i < this->cameras.size(); i++)
	{
		if(this->idObserver == this->cameras[i].id)
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(this->cameras[i].eyeX, this->cameras[i].eyeY,this->cameras[i].eyeZ,
					this->cameras[i].centerX,this->cameras[i].centerY,this->cameras[i].centerZ,
					this->cameras[i].upX,this->cameras[i].upY,this->cameras[i].upZ);

			if(this->cameras[i].id == 0)
			{
				glutSetWindowTitle("Tower Defense 3D: Main camera");
			}
			else if(this->cameras[i].id == 1)
			{
				glutSetWindowTitle("Tower Defense 3D: Tower camera");
			}
			else
			{
				glutSetWindowTitle("Tower Defense 3D: Departure camera");
			}

			break;
		}
	}
	glutPostRedisplay();
}

/**
 * Public method to rotate the observer around the axe Z
 */
void Observer::rotationZObserver(double angle)
{
	double x,y;
	for(unsigned int i = 0; i < this->cameras.size(); i++)
	{
		if(this->idObserver == this->cameras[i].id)
		{
			angle = angle*pi / 180.0;
			x = this->cameras[i].eyeX;
			y = this->cameras[i].eyeY;
			this->cameras[i].eyeX = x*cos(angle) - y*sin(angle);
			this->cameras[i].eyeY = x*sin(angle) + y*cos(angle);

			break;
		}
	}
	this->placeObserver();
}

/**
 * Public method to turn the camera
 * @param dir The direction; 1 => right,left; 2 => top,bottom
 * @param angle The angle
 */
void Observer::turnHead(int dir, double angle, int idObserver)
{
	double vect[3], vect2[3], vect3[3], Orig[3]={0, 0, 0};

	// If we turn the head of an another camera than the current
	if(idObserver == -1)
		idObserver = this->idObserver;

	for(unsigned int i = 0; i < this->cameras.size(); i++)
	{
		if(idObserver == this->cameras[i].id)
		{
			if(dir == 1) // right, left => rotation du point observe autour de l'axe Up
			{
				rotation3D(-angle, &this->cameras[i].upX, &this->cameras[i].eyeX, &this->cameras[i].centerX, vect); //rotation +
				this->cameras[i].centerX = vect[0];														//mémorisation du point observé
				this->cameras[i].centerY = vect[1];
				this->cameras[i].centerZ = vect[2];
			}
			else // top, bottom => rotation du Center Pt autour de l'axe Left
			{
				rotation3D(90, &this->cameras[i].upX, &this->cameras[i].eyeX, &this->cameras[i].centerX, vect2); //rotation du point observé, de 90 autour de l'axe Up
				vect2[0] = vect2[0] - this->cameras[i].eyeX;										//calcul de l'axe Left
				vect2[1] = vect2[1] - this->cameras[i].eyeY;
				vect2[2] = vect2[2] - this->cameras[i].eyeZ;
				rotation3D(angle, vect2, &this->cameras[i].eyeX, &this->cameras[i].centerX, vect);		//rotation du point observé autour de l'axe Left
				rotation3D(angle, vect2, &Orig[0], &this->cameras[i].upX, vect3);				//rotation de l'axe Up autour de l'axe Left
				this->cameras[i].centerX = vect[0];													//mémorisation du point observé
				this->cameras[i].centerY = vect[1];
				this->cameras[i].centerZ = vect[2];
				this->cameras[i].upX = vect3[0];												//mémorisation du Up
				this->cameras[i].upY = vect3[1];
				this->cameras[i].upZ = vect3[2];
			}
			break;
		}
	}
	this->placeObserver();
}

/**
 * Public method to zoom
 * @param step The zoom step
 */
void Observer::zoom(double step)
{
	double dx, dy, dz, dist;

	for(unsigned int i = 0; i < this->cameras.size(); i++)
	{
		if(this->idObserver == this->cameras[i].id && this->cameras[i].type)
		{
			dx = this->cameras[i].eyeX - this->cameras[i].centerX;		// determination du vecteur directeur de l'axe
			dy = this->cameras[i].eyeY - this->cameras[i].centerY;
			dz = this->cameras[i].eyeZ - this->cameras[i].centerZ;
			dist = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));	// normalisation du vecteur + multiplication par le step de deplacement
			dx = step*dx / dist;
			dy = step*dy / dist;
			dz = step*dz / dist;

			this->cameras[i].eyeX += dx;								//translation de la position de l'observateur
			this->cameras[i].eyeY += dy;

			double tmp = this->cameras[i].eyeZ;
			tmp += dz;
			if(tmp > 1)
			{
				this->cameras[i].eyeZ += dz;
			}

			this->cameras[i].centerX += dx;								//translation du point observé
			this->cameras[i].centerY += dy;
			this->cameras[i].centerZ += dz;

			break;
		}
	}
	this->placeObserver();
}

/**
 * Public method to translate the observer
 * @param dir The direction of the translation
 * @param step Translation step
 */
void Observer::translateObserver(int dir, double step)
{
	double d, vect[3];

	for(unsigned int i = 0; i < this->cameras.size(); i++)
	{
		if(this->idObserver == this->cameras[i].id && this->cameras[i].type)
		{
			if(dir == 1)
			{
				rotation3D(90, &this->cameras[i].upX, &this->cameras[i].eyeX, &this->cameras[i].centerX, vect); //rotation du point observe, de 90 autour de l'axe Up
				vect[0] = vect[0] - this->cameras[i].eyeX;											 //calcul de l'axe Left de l'obs
				vect[1] = vect[1] - this->cameras[i].eyeY;
				vect[2] = vect[2] - this->cameras[i].eyeZ;
				d = sqrt(vect[0]*vect[0] + vect[1]*vect[1] + vect[2]*vect[2]);				//nomalisation
				vect[0] = (vect[0]/d) * step;
				vect[1] = (vect[1]/d) * step;
				vect[2] = (vect[2]/d) * step;
				this->cameras[i].eyeX += vect[0];			//translation de la position de l'obs
				this->cameras[i].eyeY += vect[1];
				// Upper 0
				double tmp = this->cameras[i].eyeZ;
				tmp += vect[2];
				if(tmp > 1)
				{
					this->cameras[i].eyeZ += vect[2];
				}

				this->cameras[i].centerX += vect[0];			//translation du point observe
				this->cameras[i].centerY += vect[1];
				this->cameras[i].centerZ += vect[2];
			}
			else
			{
				//normaliser vecteur Up s'il ne l'est step a l'initialisation (=> fonction init)
				this->cameras[i].eyeX += this->cameras[i].upX * step; //translation de la position
				this->cameras[i].eyeY += this->cameras[i].upY * step;
				// Upper 0
				double tmp = this->cameras[i].eyeZ;
				tmp += vect[2];
				if(tmp > 1)
				{
					this->cameras[i].eyeZ += vect[2];
				}
				this->cameras[i].centerX += this->cameras[i].upX * step; //translation du point observe
				this->cameras[i].centerY += this->cameras[i].upY * step;
				this->cameras[i].centerZ += this->cameras[i].upZ * step;
			}

			break;
		}
	}
	this->placeObserver();
}

/**
 * 3D Rotation
 */
void Observer::rotation3D(double angle, double *axeVect, double *axePt, double *monPt, double *result)
{
	//effectue la rotation d'angle angle, d'un point de l'espace (monPt) autour d'un axe defini par son vecteur directeur axeVect,
	//et un point appartenant (axePt)

	double longueur, ux, uy, uz, m11, m12, m13, m21, m22, m23, m31, m32, m33, c, s;
	//normalisation axe de rotation
	longueur = sqrt(axeVect[0]*axeVect[0]+ axeVect[1]*axeVect[1]+ axeVect[2]*axeVect[2]);
	ux = axeVect[0]/longueur;
	uy = axeVect[1]/longueur;
	uz = axeVect[2]/longueur;
	//matrice de rotation
	c = cos(angle*pi/180);
	s = sin(angle*pi/180);
	if(abs(angle)==90)
		c=0;
	if(abs(angle)==180)
		s=0;
	m11 = ux*ux+(1-ux*ux)*c;		m12 = ux*uy*(1-c)-uz*s;		m13 = ux*uz*(1-c)+uy*s;
	m21 = ux*uy*(1-c)+uz*s;		m22 = uy*uy+(1-uy*uy)*c;		m23 = uy*uz*(1-c)-ux*s;
	m31 = ux*uz*(1-c)-uy*s;		m32 = uy*uz*(1-c)+ux*s;		m33 = uz*uz+(1-uz*uz)*c;
	//on ramene le point a tourner a l'origine avant la rotation
	ux = monPt[0] - axePt[0];
	uy = monPt[1] - axePt[1];
	uz = monPt[2] - axePt[2];
	//rotation + translation
	result[0] = m11*ux + m12*uy + m13*uz + axePt[0];
	result[1] = m21*ux + m22*uy + m23*uz + axePt[1];
	result[2] = m31*ux + m32*uy + m33*uz + axePt[2];
}

/**
 * Public method to get the number of observers in the scene
 * @return the number of observers
 */
int Observer::getNumberObservers()
{
	return this->cameras.size();
}

/**
 * Public method to retrieve the index of the tower observer
 */
int Observer::getIndexObserverTower()
{
	for(unsigned int i = 0; i < this->cameras.size(); i++)
	{
		if(this->cameras[i].id == 1)
			return i;
	}
	return 0;
}

/**
 * Setter for the type of observer
 * @param idObserver
 */
void Observer::setIdObserver(int typeObserver)
{
	this->idObserver = typeObserver;
}

/**
 * Getter for the type of observer
 * @return idObserver
 */
int Observer::getIdObserver()
{
	return this->idObserver;
}

vector<LOOKAT> Observer::getCameras()
{
	return this->cameras;
}
