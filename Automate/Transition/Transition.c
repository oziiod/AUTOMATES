#include "Transition.h"
#include <stdlib.h>
#include <stdio.h>

Tran Tran_construct(Etat* dpt, char etq, Etat* arv)
{
	Tran t ;

	t.dpt = dpt ;
	t.arv = arv ;
	t.etq = etq ;

	return t ;
}