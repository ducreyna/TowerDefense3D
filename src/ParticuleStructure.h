/*
 * ParticuleStructure.h
 *
 *  Created on: 28 d�c. 2012
 *      Author: nathan
 */

#ifndef PARTICULESTRUCTURE_H_
#define PARTICULESTRUCTURE_H_

struct PARTICLES // Cr�ation de la structure
{  bool active; // Active (1=Oui/0=Non)
   double life; // Dur�e de vie
   double fade; // Vitesse de disparition
   double r, g, b; // Valeurs RGB pour la couleur
   double x, y, z; // Position
   double xi, yi, zi; // Vecteur de d�placement
   double xg, yg, zg; // Gravit�
};


#endif /* PARTICULESTRUCTURE_H_ */
