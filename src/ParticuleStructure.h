/*
 * ParticuleStructure.h
 *
 *  Created on: 28 déc. 2012
 *      Author: nathan
 */

#ifndef PARTICULESTRUCTURE_H_
#define PARTICULESTRUCTURE_H_

struct PARTICLES // Création de la structure
{  bool active; // Active (1=Oui/0=Non)
   double life; // Durée de vie
   double fade; // Vitesse de disparition
   double r, g, b; // Valeurs RGB pour la couleur
   double x, y, z; // Position
   double xi, yi, zi; // Vecteur de déplacement
   double xg, yg, zg; // Gravité
};


#endif /* PARTICULESTRUCTURE_H_ */
