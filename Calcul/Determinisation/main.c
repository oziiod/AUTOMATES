#include <stdlib.h>
#include <stdio.h>
#include "determinisation.h"

/* fonction permettant de tester les fonctions membres de deter */
void print_etat_test(Etat** list, int size)
{
	int i = 0 ;
	for(i=0;i<size;i++)
	{
		printf("Etat %d : ",i) ;

		if(list[i]->init)
			printf("initial et ") ;
		else
			printf("non initial et ") ;

		if(list[i]->term)
			printf("terminal\n") ;
		else
			printf("non terminal\n") ;
	}
}

int main()
{
	/* on crée notre état */
	Auto Alpha = Auto_construct() ;
	auto_add_alph(&Alpha,"ab") ;
	auto_add_etat(&Alpha,Etat_construct(1,0)) ;
	auto_add_etat(&Alpha,Etat_construct(0,1)) ;
	auto_add_tran(&Alpha,0,0,'a') ;
	auto_add_tran(&Alpha,0,0,'b') ;
	auto_add_tran(&Alpha,0,1,'b') ;
	auto_add_tran(&Alpha,1,1,'a') ;
	auto_add_tran(&Alpha,1,1,'b') ;

	printf("Automate Alpha : \n") ;
	auto_print(Alpha) ;


	/* test de deter_init qui détermine les états initiaux */
	printf("Etat initiaux\n") ;
	int init_size = 0 ;
	Etat** init_list = deter_init(Alpha,&init_size) ;
	print_etat_test(init_list,init_size) ;

	/* test de deter_arv */
	printf("Etats d'arrive en partant des états initiaux et d'étiquette b\n") ;
	int arv_size = 0 ;
	Etat** arv_list = deter_arv(Alpha,&arv_size,init_list,init_size,'b') ;
	print_etat_test(arv_list,arv_size) ;

	/* test de deter_id */
	printf("Les deux états d'avant ") ;
	if(!deter_id(init_list,init_size,arv_list,arv_size)) printf("ne sont pas les mêmes\n") ;
	printf("Si on comparait une liste avec elle même elles sont ") ;
	if(deter_id(arv_list,arv_size,arv_list,arv_size)) printf("identiques\n") ;

	/* test de deter_compress */
	printf("Si on compresse la première liste du programme on obtient : ") ;
	Etat Init = deter_compress(init_list,init_size) ;
	if(Init.init) printf("un état initial et ") ;
	if(Init.term) printf("terminal\n") ; else printf("non terminal\n") ;

	printf("Si on compresse la deuxième liste du programme on obtient : ") ;
	Etat Q = deter_compress(arv_list,arv_size) ;
	if(Q.init) printf("un état initial et ") ; else printf("un état non initial et ") ;
	if(Q.term) printf("terminal\n") ; else printf("non terminal\n") ;

	printf("On déterminise Alpha \n") ;
	Auto Beta = determinisation(Alpha) ;
	auto_print(Beta) ;

	/* on tente la déterminisation d'un autre automate */
	Auto Delta = Auto_construct() ;
	auto_add_alph(&Delta,"ab") ;
	auto_add_etat(&Delta,Etat_construct(1,1)) ;
	auto_add_etat(&Delta,Etat_construct(0,0)) ;
	auto_add_tran(&Delta,0,0,'a') ;
	auto_add_tran(&Delta,0,1,'a') ;
	auto_add_tran(&Delta,1,1,'b') ;
	auto_add_tran(&Delta,1,0,'b') ;

	printf("Automate Delta : \n") ;
	auto_print(Delta) ;
	printf("On determinise Delta\n") ;
	auto_print(determinisation(Delta)) ;


	return EXIT_SUCCESS ;
}

