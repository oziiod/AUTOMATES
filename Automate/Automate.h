#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "./Etat/Etat.h"
#include "./Alphabet/Alphabet.h"
#include "./Transition/Transition.h"

#include <stdlib.h>

/* un automate c'est */
typedef struct Auto
{
	/* un alphabet */
	Alph A ;

	/* un ensemble d'etats */
	Etat* e_list ;
	int e_size ;

	/* un ensemble de transitions */
	Tran* t_list ;
	int t_size ;
} Auto ;

Auto Auto_construct() ;

void Auto_destroy(Auto* Alpha) ;

void auto_add_alph(Auto* Alpha, char string[]) ;

void auto_add_etat(Auto* Alpha, Etat Q) ;

/* dpt et arv qui sont respectivement les etats de depart et d'arrive
sont les indexes des etats dans la liste */
void auto_add_tran(Auto* Alpha, int dpt, int arv, char etq) ;

void auto_print_etat(Auto Alpha) ;

void auto_print_tran(Auto Alpha) ;

void auto_print(Auto Alpha) ;

#endif 