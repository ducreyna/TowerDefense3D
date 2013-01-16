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
	this->observer = new Observer();

	// Loading the static environnement
	landscape = new OBJECT;
	landscape->type = 0;
	landscape->statique = true;
	landscape->obj = new objLoader();
	landscape->obj->load((char *) "terrain_lo12.obj");
	this->addObject(landscape);

	this->tower = new Tower();
	this->addObject(this->tower->getObjCannon());
	this->defaultRotationCannon = false;

	for(unsigned int i = 0; i < 12; i++)
	{
		this->snowmen.push_back(new Snowman());
		this->addObject(this->snowmen[this->snowmen.size()-1]->getSnowman());
	}

	this->nbSnowmen = 0;

	this->currentTexture = -1;
	this->initSnow();
}

Scene::~Scene() {}

/**
 * Method for drawing the scene
 */
void Scene::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);			// Erase the screen
	glClear(GL_DEPTH_BUFFER_BIT);			// Erase the z-buffer

	// Default cannon direction
	if(!this->defaultRotationCannon)
	{
		this->tower->rotationCannon(180);
		this->defaultRotationCannon = true;
	}

	// Skybox
	for(unsigned int i = 0; i < this->observer->getCameras().size(); i++)
	{
		if(this->observer->getIdObserver() == this->observer->getCameras()[i].id)
		{
			double vect[3];
			vect[0] = this->observer->getCameras()[i].eyeX;
			vect[1] = this->observer->getCameras()[i].eyeY;
			vect[2] = this->observer->getCameras()[i].eyeZ;
			this->drawSkybox(vect);
		}
	}

	this->lights->defineSources();
	// TODO a enlever si besoin
//glColor3d(1,1,1);
	for(unsigned int i = 0; i < this->objects.size(); i++)
	{
		if(this->objects[i]->type == 1 || this->objects[i]->type == 2
				|| (this->objects[i]->type == 3 && !this->objects[i]->hide))
		{
			glPushMatrix();
			glMultMatrixd(this->objects[i]->MTRANSFO);
			drawObject(i);
			glPopMatrix();
		}
		else
		{
			drawObject(i);
		}
	}
	// Draw particles
	this->tower->dessinerParticules();
	// Display the reference x y z
	//drawRepere();

	// Draw Snow
	this->drawSnow();

	glutSwapBuffers();		// switch active window and work window
}

/**
 * Method for drawing an object
 * @param *object The object to draw in the scene
 */
void Scene::drawObject(int indexObject)
{
	for(int i = 0; i < this->objects[indexObject]->obj->faceCount; i++)
	{
		glPushMatrix();
		drawFace(indexObject, i);
		glPopMatrix();
	}
}

/**
 * Method for drawing a face
 * @param *object The object that owns the face
 * @param indexFace The index of the face
 */
void Scene::drawFace(int indexObject, int indexFace)
{
	int j,t;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Textures
	int TEX_coord[4][2] = {1, 1, 0, 1 ,0, 0, 1,0};
	int mtlIndex = this->objects[indexObject]->obj->faceList[indexFace]->material_index;
	char *filename = this->objects[indexObject]->obj->materialList[mtlIndex]->texture_filename;

	if(currentTexture != this->tabTextures[this->getIndexTexture(filename)])
	{
		if(mtlIndex != -1)
		{
			currentTexture = this->tabTextures[this->getIndexTexture(filename)];
			glBindTexture(GL_TEXTURE_2D, this->tabTextures[this->getIndexTexture(filename)]);
		}
	}


	// Couleur blanche pour la texture
	//glColor3d(1, 1, 1);
	glBegin(GL_POLYGON);

	// Set up normals Flat model
	//j = this->objects[indexObject]->obj->faceList[indexFace]->normal_index[0];
	//glNormal3dv(this->objects[indexObject]->obj->normalList[j]->e);

	// Define materials
	if(this->objects[indexObject]->obj->faceList[indexFace]->material_index != -1)
		this->lights->defineMaterials(indexObject, this->objects[indexObject]->obj->faceList[indexFace]->material_index);

	GLdouble u[3];

	for(int i = 0; i < this->objects[indexObject]->obj->faceList[indexFace]->vertex_count; i++)
	{
		j = this->objects[indexObject]->obj->faceList[indexFace]->vertex_index[i];
		u[0] = this->objects[indexObject]->obj->vertexList[j]->e[0];
		u[1] = this->objects[indexObject]->obj->vertexList[j]->e[1];
		u[2] = this->objects[indexObject]->obj->vertexList[j]->e[2];
		glNormal3dv(u);

		//t = this->objects[indexObject]->obj->faceList[indexFace]->texture_index[i];

		if (0)
				{
					glTexCoord2d(this->objects[indexObject]->obj->textureList[t]->e[0],this->objects[indexObject]->obj->textureList[t]->e[2]);
					//std::cout << this->objects[indexObject]->obj->textureList[t]->e[2] << std::endl;
				}
				else
					glTexCoord2d(TEX_coord[i][0], TEX_coord[i][1]);

		glVertex3d(this->objects[indexObject]->obj->vertexList[j]->e[0], this->objects[indexObject]->obj->vertexList[j]->e[1], this->objects[indexObject]->obj->vertexList[j]->e[2]);
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
void Scene::addObject(OBJECT *object)
{
	this->objects.push_back(object);
	// Transmit all objects in the scene for lighting treatment
	this->lights->setObjects(this->objects);
}

/**
 * Public method for removing an object in the scene
 * @param The object to remove
 */
void Scene::removeObject(OBJECT *object)
{
	bool found = false;
	for (unsigned int i = 0; !found && i < this->objects.size(); ++i)
	{
		if (this->objects[i]->obj == object->obj)
		{
			this->objects[i] = this->objects[this->objects.size() -1];
			this->objects.pop_back();
			found = true;
			free(object->obj);
		}
	}
}

/**
 * Public method to manage automatic animations
 */
void Scene::runAnimations()
{
	/* Automatic rotation of tower */
	if(this->observer->getIdObserver() != 1)
	{
		this->tower->rotationCannon(5);
			this->observer->turnHead(1,-5, this->observer->getIndexObserverTower());
			this->lights->rotateSpotTower(5, this->observer->getCameras()[this->observer->getIndexObserverTower()].centerX,
								this->observer->getCameras()[this->observer->getIndexObserverTower()].centerY,
								this->observer->getCameras()[this->observer->getIndexObserverTower()].centerZ);
	}

	/* Automatic animations for snowmen */
	int cptHidden = 0;
	for(int i = 0; i < nbSnowmen; i++)
	{
		// Leave a gap between snowmen
		if(!this->snowmen[i]->getSnowman()->hide && (i == 0
				|| abs(this->snowmen[i-1]->getPositionY()) == 13
				|| (abs(this->snowmen[i]->getPositionX() - this->snowmen[i-1]->getPositionX()) >= 0.1)
				|| abs(this->snowmen[i-1]->getPositionX()) == 10.5
				|| (abs(this->snowmen[i]->getPositionY() - this->snowmen[i-1]->getPositionY()) >= 7)))
		{
			this->snowmen[i]->run();
		}
		// If all snowmen are hidden in the scene
		if(this->snowmen[i]->getSnowman()->hide)
		{
			cptHidden ++;
			if(cptHidden == this->nbSnowmen)
				this->nbSnowmen = 0;
		}
	}

	/* Check projectiles collisions */
	this->tower->checkCollisions(this->snowmen, this->nbSnowmen);

	/* Tower Attack */
	vector<Projectile*> newCannonballs = this->tower->attack(this->snowmen, this->nbSnowmen);
	if(newCannonballs.size() != this->cannonballs.size())
	{
		if(this->cannonballs.size() == 0)
		{
			this->cannonballs = newCannonballs;
			for(unsigned int i = 0; i < this->cannonballs.size(); i++)
			{
				this->addObject(this->cannonballs[i]->getObjCannonball());
			}
		}
		else
		{
			for(unsigned int i = this->cannonballs.size(); i < newCannonballs.size(); i++)
			{
				this->addObject(newCannonballs[i]->getObjCannonball());
			}
			this->cannonballs = newCannonballs;
		}
	}
	else
		this->cannonballs = newCannonballs;

	/* Cannonballs deplacement */
	for(unsigned int i = 0; i < this->cannonballs.size(); i++)
	{
		if(!this->cannonballs[i]->getObjCannonball()->hide)
		{
			this->cannonballs[i]->run();
		}
	}
}

/**
 * Public method to launch a wave of snowmen
 * @param nbSnowmen
 */
void Scene::launchWave(int nbSnowmen)
{
	if(this->nbSnowmen == 0)
	{
		for(int i = 0; i < nbSnowmen; i++)
		{
			this->snowmen[i]->getSnowman()->hide = false;
		}
		this->nbSnowmen = nbSnowmen;
	}
}

/**
 * Public method to enable observers in the scene
 */
void Scene::enableObserver()
{
	observer->placeObserver();
}

/**
 * Getter for objects list
 */
vector<OBJECT*> Scene::getObjects()
{
	return this->objects;
}

/**
 * Getter for the Tower
 */
Tower* Scene::getTower()
{
	return this->tower;
}

/**
 * Getter for the lights
 */
Lighting* Scene::getLighting()
{
	return this->lights;
}

/**
 * Getter for the observer
 */
Observer* Scene::getObserver()
{
	return this->observer;
}

/**
 * Getter for the snowmen
 */
vector<Snowman*> Scene::getSnowmen()
{
	return this->snowmen;
}

/**
 * Public method to initiate textures
 */
void Scene::initTexture()
{
	MTEX* texture = (MTEX*) malloc(sizeof(MTEX) * 17);
	for(int i = 0; i < 17; i++)
	{
		texture[i].filename = (char*)malloc(sizeof(char)*256);
	}
	strcpy(texture[0].filename, "ressources/textures/bark4.png");
	strcpy(texture[1].filename, "ressources/textures/bark5.png");
	strcpy(texture[2].filename, "ressources/textures/castledoorwins.png");
	strcpy(texture[3].filename, "ressources/textures/dirt3_edges.png");
	strcpy(texture[4].filename, "ressources/textures/fruits&vegs.png");
	strcpy(texture[5].filename, "ressources/textures/leaves17.png");
	strcpy(texture[6].filename, "ressources/textures/leaves19.png");
	strcpy(texture[7].filename, "ressources/textures/shingles3.png");
	strcpy(texture[8].filename, "ressources/textures/stonewall6.png");
	strcpy(texture[9].filename, "ressources/textures/tile28.png");
	strcpy(texture[10].filename, "ressources/textures/tree_branches-leaves05.png");

	strcpy(texture[11].filename, "ressources/skybox/leftdark.png");
	strcpy(texture[12].filename, "ressources/skybox/rightdark.png");
	strcpy(texture[13].filename, "ressources/skybox/backdark.png");
	strcpy(texture[14].filename, "ressources/skybox/frontdark.png");
	strcpy(texture[15].filename, "ressources/skybox/botdark.png");
	strcpy(texture[16].filename, "ressources/skybox/topdark.png");

	this->tabTextures = (GLuint*)malloc(sizeof(GLuint));

	glGenTextures(17,this->tabTextures);

	for(int i = 0; i < 17; i++)
	{
		if(loaderTex.ReadPNGFromFile(&texture[i]))
		{
			printf("Impossible de lire le fichier");
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, this->tabTextures[i]);

			if(i == 15)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			glTexImage2D (GL_TEXTURE_2D, 0, texture[i].internalFormat,
						texture[i].width, texture[i].height, 0, texture[i].format,
						GL_UNSIGNED_BYTE, texture[i].texels);
		}
	}
	free(texture);
}

/**
 * Private to draw Skybox
 * @param vect An array containing observer position
 */
void Scene::drawSkybox(double *vect)
{
	float t = 20;
	float tNegative = -0.2;
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);

	glColor3d(1,1,1);

	glPushMatrix();
	glTranslated(vect[0], vect[1], vect[2]);

		glBindTexture(GL_TEXTURE_2D, this->tabTextures[11]);

	glBegin(GL_QUADS);			// X Négatif
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,-t,tNegative);
		glTexCoord2f(1.0, 0.0); glVertex3f(-t,t,tNegative);
		glTexCoord2f(1.0, 1.0); glVertex3f(-t,t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,-t,t);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->tabTextures[12]);
	glBegin(GL_QUADS);			// X Positif
		glTexCoord2f(0.0, 0.0); glVertex3f(t,t,tNegative);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,-t,tNegative);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,-t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(t,t,t);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->tabTextures[13]);
	glBegin(GL_QUADS);			// Y Négatif
		glTexCoord2f(0.0, 0.0); glVertex3f(t,-t,tNegative);
		glTexCoord2f(1.0, 0.0); glVertex3f(-t,-t,tNegative);
		glTexCoord2f(1.0, 1.0); glVertex3f(-t,-t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(t,-t,t);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->tabTextures[14]);
	glBegin(GL_QUADS);			// Y Positif
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,t,tNegative);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,t,tNegative);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,t,t);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->tabTextures[15]);
	glBegin(GL_QUADS);			// Z Négatif
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,t,tNegative);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,t, tNegative);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,-t,tNegative);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,-t,tNegative);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->tabTextures[16]);
	glBegin(GL_QUADS);			// Z Positif
	glColor3d(1,1,1);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,-t,t);
		glTexCoord2f(1.0, 1.0); glVertex3f(-t,-t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,t,t);
		glTexCoord2f(0.0, 0.0); glVertex3f(t,t,t);
	glEnd();

	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

/**
 * Private method to return the index of the texture
 * @param filename
 */
int Scene::getIndexTexture(char *filename)
{
	if(strcmp(filename, "bark4.png\n") == 0)
	{
		return 0;
	}
	else if(strcmp(filename, "bark5.png\n") == 0)
	{
		return 1;
	}
	else if(strcmp(filename, "castledoorwins.png\n") == 0)
	{
		return 2;
	}
	else if(strcmp(filename, "dirt3_edges.png\n") == 0)
	{
		return 3;
	}
	else if(strcmp(filename, "fruits&vegs.png\n") == 0)
	{
		return 4;
	}
	else if(strcmp(filename, "leaves17.png\n") == 0)
	{
		return 5;
	}
	else if(strcmp(filename, "leaves19.png\n") == 0)
	{
		return 6;
	}
	else if(strcmp(filename, "shingles3.png\n") == 0)
	{
		return 7;
	}
	else if(strcmp(filename, "stonewall6.png\n") == 0)
	{
		return 8;
	}
	else if(strcmp(filename, "tile28.png\n") == 0)
	{
		return 9;
	}
	else if(strcmp(filename, "tree_branches-leaves05.png\n") == 0)
	{
		return 10;
	}
	else return -1;
}

/**
 * Private method to generate an random number
 * @param min The limit minimum
 * @param max The limit maximum
 * @return double a random number
 */
double Scene::random(double min, double max)
{  return (double) (min + ((float) rand() / RAND_MAX * (max - min + 1.0)));
}

/**
 * Private method to initiate snow particles
 */
void Scene::initSnow()
{
	for(int i=0; i<MAX_PARTICLES; i++)
	{   particle[i].active = true;
		particle[i].life = 1.0;

		particle[i].x = random(-50,50);
		particle[i].y = random(-50,50);
		particle[i].z = 30;

		particle[i].fade = random(0.01,0.02);

		particle[i].r=1;
		particle[i].g=1;
		particle[i].b=1;

		particle[i].xi = random(-10.0,10.0);   // Vitesse alŽatoire
		particle[i].yi = random(-10.0,10.0);
		particle[i].zi = random(-1000.0,-500.0);

		particle[i].xg = 0.0;       // GravitŽ dirigŽe selon l'axe -Z
		particle[i].yg = 0.0;
		particle[i].zg = -1.0;
	}
}

/**
 * Private method to draw snom in the scene
 */
void Scene::drawSnow()
{
	for(int i=0; i<MAX_PARTICLES; i++)
	{   if(particle[i].active)
		{   float x = particle[i].x;   // On rŽcupre sa position
			float y = particle[i].y;
			float z = particle[i].z;

			glDisable(GL_LIGHTING);


			/* Dessin de carrŽs ˆ partir de deux triangles (plus rapide pour la carte video */
			glBegin(GL_TRIANGLE_STRIP);
			glColor4d(particle[i].r, particle[i].g, particle[i].b, particle[i].life);
			  glVertex3d(x+0.1,y,z+0.1); // Nord-Ouest
			  glVertex3d(x-0.1,y,z+0.1); // Nord-Est
			  glVertex3d(x+0.1,y,z-0.1); // Sud-Ouest
			  glVertex3d(x-0.1,y,z-0.1); // Sud-Est
			glEnd();

			glEnable(GL_LIGHTING);

			/* DŽplacement */
			particle[i].x += particle[i].xi/1000;
			particle[i].y += particle[i].yi/1000;
			particle[i].z += particle[i].zi/1000;

			/* GravitŽ */
			particle[i].xi += particle[i].xg;
			particle[i].yi += particle[i].yg;
			particle[i].zi += particle[i].zg;

			/* "Vie" */
			particle[i].life -= particle[i].fade;

			/* Si la particule est "morte" on la rŽgŽnre */
			if (particle[i].life < 0.0)
			{   particle[i].life = 1.0;    // Maximum de vie
				particle[i].fade = random(0.01,0.02);

				particle[i].x = random(-50,50); // On renvoie la particule au centre
				particle[i].y = random(-50,50);
				particle[i].z = 30.0;

				particle[i].xi = random(-10.0,10.0);   // Vitesse alŽatoire
				particle[i].yi = random(-10.0,10.0);
				particle[i].zi = random(-1000.0,-500.0);

				particle[i].r = 1;
				particle[i].g = 1;
				particle[i].b = 1;
			}
		}
	}
}



