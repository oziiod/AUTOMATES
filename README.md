# AUTOMATES
On tentera de programmer des automates à partir du langage C.  

## Conventions d'écriture
On prendrera soin d'établir certaines conventions pour nos variables :  
- toute variable usuelle (telle que la taille d'un objet) sera nommée en anglais (size par exemple)  
- on établit un système de notation pour toutes les entités spécifiques au sujet dont les abréviations ne dépasseront pas 4 caractères (cette liste évoluera dans le temps)
- les fonctions membres d'une structure devront commencer par l'abréviation de la structure correspondante
- les fonctions membres d'une fonction devront commencer par l'abréviation de cette fonction 

### Liste d'annotations des entités
Entité | Abréviation
--- | --- 
Alphabet | Alph
Etat | Etat
Transition | Tran
Automate | Auto

Note : ces éléments sont des objets/structures d'où il leur est attribué une majuscule mais leurs fonctions membres devront impérativement commencer par une minuscule (mis à part le constructeur et le destructeur).

### Liste d'annotations des fonctions de calcul
Fonction | Abréviation
--- | ---
Déterminisation | det

### Liste d'annotations de vocabulaire commumn
Mot de vocabulaire | Abréviation
--- | ---
Initial | init
Terminal | term

## Arborescence du code
Chaque dossier sauf le tronc comportera quatres éléments :
- un fichier d'interface type Automate.h
- un fichier contenant les fonctions type Automate.c
- un fichier appelé main.c qui permet de tester chaque les fonctions du dossier
- un fichier appelé compile qui a l'instruction gcc de compilation

Cela permettra de voir comment le code a été construit et de se remémorer l'usage de certaines fonctions plus aisément.