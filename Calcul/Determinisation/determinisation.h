#ifndef _DETERMINISATION_H_
#define _DETERMINISATION_H_

#include "../../Automate/Automate.h"

#include <stdlib.h>

/* fonctions chechant les etats initiaux */
/* elle renvoie une liste et son paramètre size permet d'en récupérer la taille */
Etat** deter_init(Auto Alpha, int* size) ;

/* cette fonction permet de trouver les états d'arrivé à partir d'états de départ
et de l'étiquette */
/* ici aussi on récupère la taille de la liste avec size */
Etat** deter_arv(Auto Alpha, int* size, Etat** dpt_list, int dpt_size, char etq) ;

/* on cherche à savoir si deux listes d'états sont différentes ou les mêmes */
/* id for identical */
int deter_id(Etat** list1, int size1, Etat** list2, int size2) ;

/* on crée un état à partir d'une liste */
Etat deter_compress(Etat** list, int size) ;

Auto determinisation(Auto Alpha) ;

#endif 