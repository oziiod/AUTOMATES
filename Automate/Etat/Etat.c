#include "Etat.h"
#include <stdlib.h>
#include <stdio.h>

Etat Etat_constructor(int init, int term)
{
	Etat q ;

	/* verifie que les données entrées correspondent aux données demandées */
	if(init == 1)
		q.init = init ;
	else
		/* sinon, on les initialise à 0 */
		q.init = 0 ;
	
	if(term == 1)
		q.term = term ;
	else
		/* sinon, on les initialise à 0 */
		q.term = 0 ;

	return q ;
}