#ifndef TRANSITION_H
#define TRANSITION_H

#include "../Etat/Etat.h"
#include "../Alphabet/Alphabet.h"

#include <stdlib.h>

typedef struct Tran
{
	/* les transitions prennent l'adresse des Etats car c'est l'unique
	moyen que l'on ait de les différencier */
	Etat* dpt ;
	Etat* arv ;
	char etq ;
} Tran ;

Tran Tran_construct(Etat* dpt, char etq, Etat* arv) ;

/* destructeur obsolète : l'adresse des etats n'est qu'une référence
void Tran_destructor(Tran t) ;*/

#endif 