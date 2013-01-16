/*
 * test.h
 *
 *  Created on: 13 dŽc. 2012
 *      Author: nathan
 */

#ifndef LIGHTSTRUCTURE_H_
#define LIGHTSTRUCTURE_H_

/* ############################## */
/* LIGHT STRUCTURE */
struct COORD
{
	GLdouble x;
	GLdouble y;
	GLdouble z;
	GLdouble w;
};

struct RGB
{
	GLdouble r;     /* rouge */
	GLdouble g;     /* vert */
	GLdouble b;     /* bleu */
};

struct ALLURE_FAISCEAU
{
        GLdouble k;
        GLdouble theta;
};


struct LIGHT_SOURCE
{
	/*
	 * 0 => global
	 * 1 => departure + arrival + tower spots
	 */
	int id;
	RGB             ambiant;         /* couleur "ambiente" */
	RGB             color;          /* couleur de la source */
	COORD           position;         /* position de la source */
	ALLURE_FAISCEAU allure_faisceau;  /* allure du faisceau lumineux */
	COORD           direction;        /* direction du faisceau lumineux */
	GLint		on;
};
/* ############################## */



#endif /* LIGHTSTRUCTURE_H_ */
