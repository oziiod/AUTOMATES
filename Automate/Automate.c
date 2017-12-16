#include "Automate.h"
#include <stdlib.h>
#include <stdio.h>

Auto Auto_construct()
{
	Auto Alpha ;

	Alpha.A = Alph_construct() ;

	Alpha.e_list = NULL ;
	Alpha.e_size = 0 ;

	Alpha.t_list = NULL ;
	Alpha.t_size = 0 ;

	return Alpha ;
}

void Auto_destroy(Auto* Alpha)
{
	Alph_destroy(&Alpha->A) ; 

	free(Alpha->e_list) ;
	Alpha->e_size = 0 ;

	free(Alpha->t_list) ;
	Alpha->t_size = 0 ;
} 

void auto_add_alph(Auto* Alpha, char string[])
{
	int i = 0 ;
	while(string[i] != '\0')
	{
		/* on passe l'adresse de l'aphabet */
		alph_add(&Alpha->A,string[i]) ;
		i++ ;
	}
}

void auto_add_etat(Auto* Alpha, Etat Q)
{
	Alpha->e_size ++ ;
	Alpha->e_list = (Etat*) realloc(Alpha->e_list,Alpha->e_size*sizeof(Etat)) ;
	Alpha->e_list[Alpha->e_size-1] = Q ;
}

void auto_add_tran(Auto* Alpha, int dpt, int arv, char etq)
{
	int i = 0 , etq_exist = 0 , etat_exist = 0 ;

	/* on vérifie d'abord que l'étiquette est dans l'alphabet */
	while(i < Alpha->A.size && !etq_exist)
	{
		if(etq == Alpha->A.list[i]) etq_exist = 1 ;
		i++ ;
	}

	/* on verifie que les indexes fournies correspondent à ceux existant dans le tableau */
	if((dpt >= Alpha->e_size || arv >= Alpha->e_size) || (dpt < 0 || arv < 0)) etat_exist = 1 ;

	if(etq_exist && !etat_exist)
	{
		Alpha->t_size++ ;
		Alpha->t_list = (Tran*) realloc(Alpha->t_list,Alpha->t_size*sizeof(Tran)) ;
		Alpha->t_list[Alpha->t_size-1] = Tran_construct(&Alpha->e_list[dpt],etq,&Alpha->e_list[arv]) ;
	}
	else
	{
		printf("Erreur : l'étiquette ne fait pas partie de l'alphabet\n") ; 
		printf("ou les indexes fournis n'existent pas dans le tableau\n") ;
	}
}

void auto_print_etat(Auto Alpha)
{
	int i = 0 ;
	for(i=0;i<Alpha.e_size;i++)
	{
		printf("Etat %d : ",i) ;

		if(Alpha.e_list[i].init)
			printf("initial et ") ;
		else
			printf("non initial et ") ;

		if(Alpha.e_list[i].term)
			printf("terminal\n") ;
		else
			printf("non terminal\n") ;
	}
}

void auto_print_tran(Auto Alpha)
{
	int i=0 ;

	for(i=0;i<Alpha.t_size;i++)
	{
		int dpt = -1, arv = -1, j = 0 ;
		/* doit forcément trouver un état avec la meme addresse
		car une transition est initialisé avec l'adresse d'un état */
		while(dpt== -1 || arv == -1)
		{
			if(Alpha.t_list[i].dpt == &Alpha.e_list[j]) dpt = j ;
			if(Alpha.t_list[i].arv == &Alpha.e_list[j]) arv = j ;
			j++ ;
		}
		printf("Transition %d : (%d,%c,%d)\n",i,dpt,Alpha.t_list[i].etq,arv) ;
	}
}  

void auto_print(Auto Alpha)
{
	/* divers compteurs */
	int i = 0, j = 0, k = 0, l = 0, m = 0;
	/* nombre maximum d'etat pour une etiquette */
	int nb_etat = 0 ;
	/* variable servant a un affichage propre */
	int ecart = Alpha.e_size * 2 ;

	printf("Etats/Symboles | ") ;
	for(i=0;i<Alpha.A.size;i++)
	{
		printf("%c",Alpha.A.list[i]) ;
		/* met ecart nombre d'espaces */
		for(j=0;j<ecart;j++) { printf(" ") ; }
		printf("| ") ;
	}
	printf("\n") ;

	/* on parcours tous les etats dont on affiche les transitions */
	for(i=0;i<Alpha.e_size;i++)
	{
		/* affiche les etats et leur symboles associes */
		int init = Alpha.e_list[i].init ;
		int term = Alpha.e_list[i].term ;
		if(init && term)
		{
			/* etats/symboles fait 14 car d'ou 11+3symboles */
			printf("->*%11d | ",i) ;
		}
		else if (init)
		{
			printf("->%12d | ",i) ;
		}
		else if (term)
		{
			printf("*%13d | ",i) ;
		}
		else
		{
			printf("%14d | ",i) ;
		}

		/* parcours les lettres qui sont nos colonnes */
		for(j=0;j<Alpha.A.size;j++)
		{
			nb_etat = 0 ;
			/* parcours les transitions pour obtenir celle ayant la meme etiquette que nos colonnes */
			for(k=0;k<Alpha.t_size;k++)
			{
				/* cherche la bonne etiquette */
				if(Alpha.t_list[k].etq == Alpha.A.list[j])
				{			
					/* cherche le bon debut qui est l'etat i */	
					if(Alpha.t_list[k].dpt == &Alpha.e_list[i])
					{
						/* si les conditions sont respectees on a donc un etat accessible
						de i par la transition d'etiquette j */
						/* on cherche donc l'indexe de l'etat correspondant a la transition k dans notre liste d'etat */
						l = -1 ;
						int indexe = -1 ;
						while(indexe == -1)
						{
							/* phenomene bizzare avec le l++ : s'incremente une derniere fois meme si sorti de la boucle */
							l++ ;
							if(Alpha.t_list[k].arv == &Alpha.e_list[l])
							{
								indexe = l ;
							}
						}
						printf("%d ",l) ;
						nb_etat += 2 ; /* on a affiche un etat (a prendre en compte pour l'affichage final) */
					}
				} 
			}
			/* avant de passer a la prochaine lettre on comble les ecarts */
			for(m=0;m<ecart-nb_etat;m++) { printf(" ") ; } printf(" | ") ;
		}
		/* passe au prochain etat */
		printf("\n") ;
	}
}