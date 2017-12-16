#include "Automate.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	Auto Alpha = Auto_construct() ;

	/* ajoute un alphabet */
	auto_add_alph(&Alpha,"ab") ;
	printf("L'alphabet de notre automate : ") ;
	alph_print(Alpha.A) ;

	/* ajoute des etats */
	auto_add_etat(&Alpha,Etat_construct(1,1)) ;
	auto_add_etat(&Alpha,Etat_construct(0,0)) ;

	/* ajoute des transition */
	auto_add_tran(&Alpha,0,1,'a') ;
	auto_add_tran(&Alpha,1,0,'a') ;
	auto_add_tran(&Alpha,0,0,'b') ;
	auto_add_tran(&Alpha,1,1,'b') ;
	/* deux transitions ne pouvant exister */
	auto_add_tran(&Alpha,90,1,'a') ;
	auto_add_tran(&Alpha,1,1,'c') ;

	/* on affiche les états */
	auto_print_etat(Alpha) ;

	/* on affiche les transitions */
	auto_print_tran(Alpha) ;

	/* on affiche l'automate */
	auto_print(Alpha) ;

	Auto_destroy(&Alpha) ;

	return EXIT_SUCCESS ;
}