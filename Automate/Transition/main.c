#include "Transition.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/* on construit les élément essentiels à la construction d'une transistion */
	/* un alphabet */
	Alph A = Alph_construct() ;
	alph_add(&A,'a') ;

	/* deux états */
	Etat q1 = Etat_construct(1,0) ;
	Etat q2 = Etat_construct(0,1) ;

	/* on crée la transition */
	Tran t = Tran_construct(&q1,A.list[0],&q2) ;

	return EXIT_SUCCESS ;
}