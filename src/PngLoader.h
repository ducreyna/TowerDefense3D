/*
 * PngLoader.h
 *
 *  Created on: 2 janv. 2013
 *      Author: nathan*/


#ifndef PNGLOADER_H_
#define PNGLOADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include <libpng15/png.h>
#include <libpng15/pngconf.h>
#include <libpng15/pnglibconf.h>
#include "ObjectStructure.h"


#if defined(__APPLE__) && defined(__MACH__)
        #include <GLUT/glut.h>
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
#else
		#include <glut.h>
        #include <GL/gl.h>
        #include <GL/glu.h>
#endif



using namespace std;

class PngLoader {
public:
	PngLoader();
	virtual ~PngLoader();

	int ReadPNGFromFile (MTEX *texinfo);
	void GetPNGtextureInfo (int color_type, MTEX *texinfo);
};

#endif  PNGLOADER_H_
