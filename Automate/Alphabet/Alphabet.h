#ifndef ALPHABET_H
#define ALPHABET_H

#include <stdlib.h>

typedef struct Alph
{
	/* liste des caractères */
	char* list ;
	/* taille de l'alphabet */
	int size ;
} Alph ;

/* constructeur */
Alph Alph_construct() ;

/* destructeur */
void Alph_destroy(Alph* A) ;

void alph_add(Alph* A, char c) ;

void alph_print(Alph A) ;

#endif