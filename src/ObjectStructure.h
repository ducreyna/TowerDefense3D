/*
 * ObjectStructure.h
 *
 *  Created on: 16 déc. 2012
 *      Author: nathan
 */

#ifndef OBJECTSTRUCTURE_H_
#define OBJECTSTRUCTURE_H_

#include "objLoader.h"
#if defined(__APPLE__) && defined(__MACH__)
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

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
	/*
	 * true => object hidden
	 */
	bool hide;

	/*
	 * true => statique
	 */
	bool statique;
};

struct MTEX
{
        char *filename;
        GLint width;
        GLint height;
        GLenum format;
        GLint internalFormat;
        GLubyte *texels;
        GLuint glnum;
};


#endif /* OBJECTSTRUCTURE_H_ */
