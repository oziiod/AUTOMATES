#include "Alphabet.h"
#include <stdlib.h>
#include <stdio.h>

Alph Alph_construct()
{
	Alph A ;

	A.list = NULL ;
	A.size = 0 ;

	return A ;
}

void Alph_destroy(Alph* A)
{
	/* libère la liste */
	free(A->list) ;
	A->size = 0 ;
	/* libère A */
	free(A) ;
}

void alph_add(Alph* A, char c) 
{
	/* bool exist : verifie si c n'appartient pas déjà à l'alphabet */
	int i = 0 , exist = 0 ;

	for(i=0;i<A->size;i++)
	{
		if(c == A->list[i]) exist = 1 ;
	}

	if(!exist)
	{
		A->size++ ;
		A->list = (char*) realloc(A->list,A->size*sizeof(char)) ;
		A->list[A->size-1] = c ;
	}
	else
	{
		printf("Erreur : la lettre appartient déjà à l'alphabet\n") ;
	}
}

void alph_print(Alph A)
{
	int i = 0 ;

	if(A.size == 0)
	{
		printf("Alphabet vide\n");
	}
	else
	{
		printf("%c",'{') ;
		for(i=0;i<A.size-1;i++)
		{
			printf("%c,",A.list[i]);
		}
		printf("%c}\n",A.list[A.size-1]) ;
	}
}