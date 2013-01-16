/*
 * Interactions.cpp
 *
 *  Created on: 17 dŽc. 2012
 *      Author: nathan
 */

#include "Interactions.h"

Interactions::Interactions(Scene *scene, int width, int height) {
	this->width = width;
	this->height = height;
	curX = 0;
	curY = 0;

	this->scene = scene;
}

Interactions::~Interactions() {}

/**
 * Public method to manage alphanumeric keys of the keyboard
 * @param key The key pressed
 */
void Interactions::keyPressed(unsigned char key)
{
	int idObserver = this->scene->getObserver()->getIdObserver();
	int shift = 0;
	float zoomStep = 0.5;
	double stepTrans = 0.5;

	if(glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		shift=1;

	switch(key)
	{
	case 'o':
	{
		idObserver ++;
		if(idObserver == (this->scene->getObserver()->getNumberObservers()))
		{
			this->scene->getObserver()->setIdObserver(0);
		}
		else
		{
			this->scene->getObserver()->setIdObserver(idObserver);
		}
		curX = 0;
		curY = 0;
	} break;
	case 'z':
	{
		this->scene->getObserver()->zoom(-zoomStep);
	} break;
	case 's':
	{
		this->scene->getObserver()->zoom(zoomStep);
	} break;
	case 'q':
	{
		this->scene->getObserver()->translateObserver(1, stepTrans);
	} break;
	case 'd':
	{
		this->scene->getObserver()->translateObserver(1, -stepTrans);
	} break;
	case 'l':
	{
		this->scene->getLighting()->switchLighting();
	} break;
	}
	this->scene->getObserver()->placeObserver();
}

/**
 * Public method to manage special keys pressed on the keyboard
 * @param key The key pressed
 */
void Interactions::specialKeyPressed(int key)
{
	switch(key)
	{
	case GLUT_KEY_F1:
	{
		this->scene->launchWave(1);
	} break;
	case GLUT_KEY_F2:
	{
		this->scene->launchWave(2);
	} break;
	case GLUT_KEY_F3:
	{
		this->scene->launchWave(3);
	} break;
	case GLUT_KEY_F4:
	{
		this->scene->launchWave(4);
	} break;
	case GLUT_KEY_F5:
	{
		this->scene->launchWave(5);
	} break;
	case GLUT_KEY_F6:
	{
		this->scene->launchWave(7);
	} break;
	case GLUT_KEY_F8:
	{
		this->scene->launchWave(8);
	} break;
	case GLUT_KEY_F9:
	{
		this->scene->launchWave(9);
	} break;
	case GLUT_KEY_F10:
	{
		this->scene->launchWave(10);
	} break;
	case GLUT_KEY_UP:
	{
		this->scene->getTower()->increasePower();
	} break;
	case GLUT_KEY_DOWN:
	{
		this->scene->getTower()->decreasePower();
	} break;
	case GLUT_KEY_RIGHT:
	{
		for(unsigned int i = 0; i < this->scene->getSnowmen().size(); i++)
		{
			if(!this->scene->getSnowmen()[i]->getSnowman()->hide)
			{
				this->scene->getSnowmen()[i]->increasePV();
			}
		}
	} break;
	case GLUT_KEY_LEFT:
	{
		for(unsigned int i = 0; i < this->scene->getSnowmen().size(); i++)
		{
			if(!this->scene->getSnowmen()[i]->getSnowman()->hide)
			{
				this->scene->getSnowmen()[i]->decreasePV();
			}
		}
	} break;
	}
}

/**
 * Public method to manage the mouse moves
 * @param x position of the mouse
 * @param y position of the mouse
 */
void Interactions::mouseMove(int x, int y)
{
	bool moveOk;
	double deltaX, deltaY;

	if(curX == 0 && curY == 0) moveOk = false;
	else moveOk = true;

	if(curX == x && x <= 0) deltaX = -10;
		else if(curX == x && x >= width) deltaX = 10;
		else
		{
			deltaX = x - curX; //calcul du mouvement par rapport a la position sauvegardee
			curX = x;			//sauvegarde de nouveau pour repartir de la au prochain mouvement
		}
	if(curY == y && y <= 0) deltaY = -10;
		else if(curY == y && y >= height) deltaY = 10;
	else
	{
		deltaY = y - curY;
		curY = y;
	}

	if(this->scene->getObserver()->getIdObserver() == 1)
	{
		if(moveOk)
		{
			this->scene->getObserver()->turnHead(1,deltaX/2);

			// Turn the cannon with the camera
			this->scene->getTower()->rotationCannon(-deltaX/2);
			this->scene->getLighting()->rotateSpotTower(-deltaX/2, this->scene->getObserver()->getCameras()[this->scene->getObserver()->getIndexObserverTower()].centerX,
					this->scene->getObserver()->getCameras()[this->scene->getObserver()->getIndexObserverTower()].centerY,
					this->scene->getObserver()->getCameras()[this->scene->getObserver()->getIndexObserverTower()].centerZ);
		}
	}
	else
	{
		// Head rotation
		if(moveOk)
		{
			this->scene->getObserver()->turnHead(1,deltaX/2);
			this->scene->getObserver()->turnHead(2,deltaY/2);

			// TODO penser a une solution pour bloquer sur -Z et Z
			// Avoid infinate rotation on Z
			/*for(unsigned int i = 0; i < this->scene->getObserver()->getCameras().size(); i++)
			{
				cout << deltaY << endl;
				if(this->scene->getObserver()->getIdObserver() == this->scene->getObserver()->getCameras()[i].id)
				{
					if((int)(this->scene->getObserver()->getCameras()[i].upZ * 10) >= 0 || deltaY < 0)
					{
						this->scene->getObserver()->turnHead(2,deltaY/2);
					}
					else if(deltaY < 0)
					{

					}
				}
			}*/
		}
	}

	this->scene->getObserver()->placeObserver();
}

/**
 * Method to set the window size
 * @param Width the window width
 * @param Width the window height
 */
void Interactions::setWindowSize(int width, int height)
{
	this->width = width;
	this->height = height;
}
