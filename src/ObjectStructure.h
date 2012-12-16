/*
 * ObjectStructure.h
 *
 *  Created on: 16 dŽc. 2012
 *      Author: nathan
 */

#ifndef OBJECTSTRUCTURE_H_
#define OBJECTSTRUCTURE_H_

#include "objLoader.h"

struct OBJECT
{
	/*
	 * 0 => landscape
	 * 1 => tower
	 * 2 => snowman
	 * 3 => projectile
	 */
	int type;
	GLdouble MTRANSFO[16];
	objLoader* obj;
};


#endif /* OBJECTSTRUCTURE_H_ */
