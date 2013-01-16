/*
 * Observer.h
 *
 *  Created on: 16 déc. 2012
 *      Author: nathan
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#if defined(__APPLE__) && defined(__MACH__)
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#define pi 3.14159265

#include <vector.h>
#include <cmath>
#include "ObserverStructure.h"

using namespace std;

class Observer {
public:
	Observer();
	virtual ~Observer();

	/* Public methods */
	void placeObserver();
	void rotationZObserver(double angle);
	void turnHead(int dir, double angle, int idOberser=-1);
	void zoom(double pas);
	void translateObserver(int dir, double pas);
	void rotation3D(double angle, double* axeVect, double *axePt, double* monPt, double* result);
	int getNumberObservers();
	int getIndexObserverTower();

	/* Setters and Getters */
	int getIdObserver();
	vector<LOOKAT> getCameras();
	void setIdObserver(int idObserver);

private:
	/* Attributes */
	vector<LOOKAT> cameras;
	int idObserver;
};

#endif /* OBSERVER_H_ */
