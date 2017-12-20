#include <stdlib.h>
#include <stdio.h>
#include "determinisation.h"


Etat** deter_init(Auto Alpha, int* size) 
{
	int i = 0 ;
	/* on evite toute erreur en repassant size à 0 */
	*size = 0 ;
	/* on initialise la liste des etats initiaux */
	Etat** init_list = NULL ;

	for(i=0;i<Alpha.e_size;i++)
	{
		if(Alpha.e_list[i].init)
		{
			(*size)++ ;
			init_list = (Etat**) realloc(init_list,(*size)*sizeof(Etat*)) ;
			init_list[*size-1] = &Alpha.e_list[i] ;
		}
	}

	return init_list ;
}

Etat** deter_arv(Auto Alpha, int* size, Etat** dpt_list, int dpt_size, char etq)
{
	int i = 0 , j = 0 ;
	*size = 0 ;
	Etat** arv_list = NULL ;

	/* on cherche dans l'ensemble des états de depart... */
	for(i=0;i<dpt_size;i++)
	{
		/* ...l'ensemble des transitions... */
		for(j=0;j<Alpha.t_size;j++)
		{
			/* dont l'état de départ appartient à la liste 
			et qui a la même étiquette que celle passée en paramètre */
			if(Alpha.t_list[j].etq == etq && Alpha.t_list[j].dpt == dpt_list[i])
			{
				/* on vérifie que l'état n'appartient pas déjà à la liste */
				int exist = 0 , k = 0 ;
				while(k < *size && !exist)
				{
					if(arv_list[k] == Alpha.t_list[j].arv) exist = 1 ;
					k++ ;
				}
				
				/* s'il n'y est pas déjà on l'y rajoute */
				if(!exist)
				{
					(*size)++ ;
					arv_list = (Etat**) realloc(arv_list,(*size)*sizeof(Etat*)) ;
					arv_list[*size-1] = Alpha.t_list[j].arv ;
				}
			}
		}
	}

	return arv_list ; 
}

int deter_id(Etat** list1, int size1, Etat** list2, int size2)
{
	/* id pour identical */
	int id = 0 , i = 0 , j = 0 ;

	/* si leurs tailles sont différentes elles ne sont pas les mêmes */
	if(size1 == size2)
	{
		/* on va compter le nombre d'état identique, s'il est égal au nombre d'état
		total à la sortie alors nos deux listes sont identiques */
		int nb_id = 0 ; 
		while(!id && i < size1)
		{
			for(j=0;j<size1;j++)
			{
				if(list1[i] == list2[j]) nb_id++ ;
			}
			/* il n'y a pas de risque de doublons dans la déterminisation 
			donc on sort de la boucle dès que les tailles sont les mêmes */
			/* et au contraire si deux listes sont exactement les mêmes (sans commutativité)
			alors on risque de compter trop d'états identiques */
			if(nb_id == size1) id = 1 ;
			i++ ;
		}
	}

	return id ;
}

Etat deter_compress(Etat** list, int size)
{
	/* l'état est terminal si l'un de ses états est terminal 
	mais n'est inital que si tous ses états sont initiaux */
	int term = 0 , init = 0 , nb_init = 0 , i = 0 ;

	for(i=0;i<size;i++)
	{
		if(list[i]->init) nb_init++ ;
		if(list[i]->term) term = 1 ;
	}

	if(nb_init == size) init = 1 ; 

	return Etat_construct(init,term) ;
}

Auto determinisation(Auto Alpha)
{
	int i = 0 , j = 0  ;
	Auto Beta = Auto_construct() ;

	/* on commence par reprendre l'alphabet d'Alpha */
	/* on copie la taille */
	Beta.A.size = Alpha.A.size ;
	/* il ne faut pas que les listes de caractères aient la meme adresse */
	/* ainsi on en crée une nouvelle */
	Beta.A.list = (char*) malloc(Alpha.A.size*sizeof(char)) ;
	for(i=0;i<Alpha.A.size;i++)
	{
		Beta.A.list[i] = Alpha.A.list[i] ;
	}

	/* on doit maintenant déterminer les états et les transitions */

	/* variables essentielles aux états */
	int e_size = 1 ;
	/* on stocke des listes d'adresses d'états */
	int* e_list_size = (int*) malloc(e_size*sizeof(int)) ;
	Etat*** e_list = (Etat***) malloc(e_size*sizeof(Etat**)) ;
	/* on y met les états initiaux */
	e_list[0] = deter_init(Alpha,&e_list_size[0]) ;

	/* variables essentielles aux transitions */
	/* on va ici crée une matrice de liste d'état :
		- en colonne 0 on aura les états de départ 
		- en colonne 1 on aura les états d'arrivé correspondants */
	int t_size = 0 ;
	Etat**** t_list = (Etat****) malloc(2*sizeof(Etat***)) ;
	t_list[0] = NULL ;
	t_list[1] = NULL ;
	int** t_list_size = (int**) malloc(2*sizeof(int*)) ;
	t_list_size[0] = NULL ;
	t_list_size[1] = NULL ;

	i = 0 ;
	/* on parcours les etats, on a forcement un nombre fini d'etats */
	/* dans la boucle e_size-1 correspond à i */
	while(i < e_size)
	{
		/* on parcourt l'alphabet */
		for(j=0;j<Alpha.A.size;j++)
		{
			t_size++ ;
			t_list[0] = (Etat***) realloc(t_list[0],t_size*sizeof(Etat**)) ;
			t_list[1] = (Etat***) realloc(t_list[0],t_size*sizeof(Etat**)) ;
			t_list_size[0] = (int*) realloc(t_list_size[0],t_size*sizeof(int)) ;
			t_list_size[1] = (int*) realloc(t_list_size[1],t_size*sizeof(int)) ;

			/* l'etat en [i] est celui de départ */
			t_list[0][t_size-1] = e_list[e_size-1] ;
			t_list_size[0][t_size-1] = e_list_size[e_size-1] ;

			/* on crée la liste des états d'arrivé et sa taille */
			int arv_size = 0 ;
			Etat** arv_etat = deter_arv(Alpha,&arv_size,e_list[e_size-1],e_list_size[e_size-1],Alpha.A.list[j]) ;

			/* on les insère dans le tableau d'arrivé */
			t_list[1][t_size-1] = arv_etat ;
			t_list_size[1][t_size-1] = arv_size ;

			/* on doit vérifier que l'état n'y existe pas déjà avant de l'ajouter */
			int exist = 0 , k = 0 ;
			while(k < e_size && !exist)
			{
				if(deter_id(arv_etat,arv_size,e_list[k],e_list_size[k])) exist = 1 ;
				k++ ;
			}
			
			if(!exist)
			{
				e_size++ ;
				e_list_size = (int*) malloc(e_size*sizeof(int)) ;
				e_list = (Etat***) malloc(e_size*sizeof(Etat**)) ;

				e_list_size[e_size-1] = arv_size ;
				e_list[e_size-1] = arv_etat ;
			}
		}
		i++ ;
	}

	/* on a maintenant obtenu la liste des états qu'on prend soin de compresser en de nouveaux états */
	/* on fait les allocations nécessaires */
	Beta.e_size = e_size ;
	Beta.e_list = (Etat*) malloc(e_size*sizeof(Etat)) ;
	for(i=0;i<e_size;i++)
	{
		/* et on les insère */
		Beta.e_list[i] = deter_compress(e_list[i],e_list_size[i]) ;
	}

	/* on doit maintenant créer et insérer les transitions */
	Beta.t_size = t_size ;
	Beta.t_list = (Tran*) malloc(t_size*sizeof(Tran)) ;
	/* il faut chercher l'état correspondant dans notre liste */
	for(i=0;i<t_size;i++)
	{
		int dpt_index = 0 , arv_index = 0 , exist = 0 ;

		for(j=0;j<e_size;j++)
		{
			if(deter_id(t_list[0][i],t_list_size[0][i],e_list[j],e_list_size[j])) dpt_index = j ;
			if(deter_id(t_list[1][i],t_list_size[1][i],e_list[j],e_list_size[j])) arv_index = j ; 
		}


		/* on doit aussi vérifier si la transition qu'on essaie de mettre dans notre liste n'y existe pas deja */
		/* on parcourt les elements de t_list - qui s'arretent a i ducoup */
		for(j=0;j<i;j++)
		{
			/* et on verifie si une transition du meme genre existe deja */
			if(Beta.t_list[j].dpt == &Beta.e_list[dpt_index]
				&& Beta.t_list[j].arv == &Beta.e_list[arv_index]
				&& Beta.t_list[j].etq == Beta.A.list[i%Beta.A.size])
				exist = 1 ;
		}

		/* on y met la transistion si elle n'y existe pas */
		if(!exist) Beta.t_list[i] = Tran_construct(&Beta.e_list[dpt_index],Beta.A.list[i%Beta.A.size],&Beta.e_list[arv_index]) ;
	}

	return Beta ;
}
