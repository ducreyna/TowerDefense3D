/*
 * ObserverStructure.h
 *
 *  Created on: 17 dŽc. 2012
 *      Author: nathan
 */

#ifndef OBSERVERSTRUCTURE_H_
#define OBSERVERSTRUCTURE_H_

struct LOOKAT
{
	/*
	 * 0 => global camera
	 * 1 => tower camera
	 * 2 => departure cameras
	 */
	int id;

	/*
	 * 0 => fixed
	 * 1 => mobile
	 */
	int type;

	double eyeX;
	double eyeY;
	double eyeZ;

	double centerX;
	double centerY;
	double centerZ;

	double upX;
	double upY;
	double upZ;
};


#endif /* OBSERVERSTRUCTURE_H_ */
