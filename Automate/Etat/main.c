#include "Etat.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/* on crée un Etat */
	Etat q = Etat_construct(1,5) ;

	if (q.init) { puts("Initial") ; } else { puts("Non initial") ; }
	if (q.term) { puts("Terminal") ; } else { puts("Non terminal") ; }

	return EXIT_SUCCESS ;
}