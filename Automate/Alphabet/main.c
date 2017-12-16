#include "Alphabet.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/* on crée un alphabet */
	Alph A = Alph_construct() ;

	/* on y ajoute plusieurs lettres */
	alph_add(&A,'a') ;
	alph_add(&A,'b') ;
	alph_add(&A,'c') ;

	/* on essaie d'y ajouter une lettre existante */
	alph_add(&A,'a') ;

	/* on affiche l'alphabet */
	alph_print(A) ;

	/* on détruit notre alphabet */
	Alph_destroy(&A) ;
	return EXIT_SUCCESS ;
}