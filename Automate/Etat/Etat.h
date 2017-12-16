#ifndef ETAT_H
#define ETAT_H

#include <stdlib.h>

typedef struct Etat
{
	int init ;
	int term ;
} Etat ;

/* prend 0 ou 1 en arg */
Etat Etat_construct(int init, int term) ;

/* fonction obsolète car aucun pointeur donc aucune destruction à gérer
void Etat_destructor(Etat q) ; */

#endif