#include "sdata.h"
#include "stdio.h"
#include  <stdlib.h>

int Puis2(int Valeur){
	if(Valeur)
		return 2*Puis2(Valeur-1);
	return 1;
}

int ioc(unsigned char c){
	return c;
}

void creerArbreBinaire(int hauteur, ArbreSymbole * arbre)
{
	if(hauteur ==0){
		arbre->valeur = 0;
		arbre->occurrence = 0;
		arbre->taille = 0;
		arbre->filsDroit = NULL;
		arbre->filsGauche = NULL;
		return;
	}
	arbre->taille = 0;
	arbre->occurrence = 0;
	arbre->valeur = 0;
	(arbre)->filsDroit = malloc(sizeof(ArbreSymbole));
	(arbre)->filsGauche = malloc(sizeof(ArbreSymbole));
	creerArbreBinaire(hauteur-1, arbre->filsDroit);
	creerArbreBinaire(hauteur-1, arbre->filsGauche);
}

void creerArbreBinaireEntier(int hauteur, ArbreEntier * arbre)
{
	if(hauteur ==0){
		arbre->filsDroit = NULL;
		arbre->filsGauche = NULL;
		arbre->valeur = 0;
		arbre->taille = 0;
		return;
	}
	arbre->valeur=0;
	arbre->taille = 0;
	(arbre)->filsDroit = malloc(sizeof(ArbreEntier));
	(arbre)->filsGauche = malloc(sizeof(ArbreEntier));
	creerArbreBinaireEntier(hauteur-1, arbre->filsDroit);
	creerArbreBinaireEntier(hauteur-1, arbre->filsGauche);
}

ArbreEntier * creerArbreEntierVide(int valeur)
{
	ArbreEntier * a = malloc(sizeof(ArbreEntier));
	a->valeur = valeur;
	a->taille = 0;
	a->filsGauche=NULL;
	a->filsDroit=NULL;
	return a;
}

//Changé
int nombreOccurrence(ArbreEntier * arbre, unsigned char symbole)
{
	ArbreEntier * a = arbre;
	int direction;
	int indiceSymbole = 8;

	while(!estFeuilleEntier(a)){
		direction=symbole/indiceSymbole;
		symbole=symbole%indiceSymbole;
		indiceSymbole--;
		if (direction)
			a = a->filsGauche;
		else
			a = a->filsDroit;
	}
	return a->valeur;
}


int estFeuille(ArbreSymbole * arbre)
{
	if((arbre->filsDroit==NULL)&&(arbre->filsGauche==NULL)) return 1;
	return 0;
}

int estFeuilleEntier(ArbreEntier * arbre)
{
	if((arbre->filsDroit==NULL)&&(arbre->filsGauche==NULL)) return 1;
	return 0;
}

ArbreEntier * ajouterNoeudParent(ArbreEntier * fils, char direction)
{
	ArbreEntier * arbre;
	if(direction == 'd' || direction =='D'){
		arbre = malloc(sizeof(ArbreEntier));
		arbre->filsDroit = fils;
	}
	else if (direction == 'g' || direction =='G'){
		arbre = malloc(sizeof(ArbreEntier));
		arbre->filsGauche = fils;
	}
	else return NULL;
	
	return arbre;
}



ArbreSymbole * creerArbreSymboleVide(char valeur, int occurrence)
{
	ArbreSymbole * a = malloc(sizeof(ArbreSymbole));
	a->valeur = valeur;
	a->occurrence = occurrence;
	a->taille = 0;
	a->filsGauche=NULL;
	a->filsDroit=NULL;
	return a;
}
void ajouterOccurenceAbreSymbole(ArbreSymbole * a, char * symbole)
{
	if (a == NULL) return;
	ArbreSymbole * noeudCourant;
	char bit,MASK = 0x1;
	int bitCourant;
	noeudCourant = a;
	for (bitCourant = 7; bitCourant >= 0; bitCourant--)
	{
		bit = ((MASK << bitCourant)&*symbole) >> bitCourant;
		if (bit==0x1)
		{
			if (noeudCourant->filsDroit != NULL)
			{
				noeudCourant = noeudCourant->filsDroit;
			}
		}
		if (bit == 0x0)
		{
			if (noeudCourant->filsGauche != NULL)
			{
				noeudCourant = noeudCourant->filsGauche;
			}
		}
	}
	if (estFeuille(noeudCourant))
	{
		noeudCourant->valeur= *symbole;
		noeudCourant->occurrence++;
	}
	else
	{
		printf("sdata.c : ajouterOccurenceArbreEntier erreur\n"); exit(0);
	}
}



ArbreSymbole * ajout2ArbresS(ArbreSymbole * a1, ArbreSymbole * a2){
	ArbreSymbole* a3 = creerArbreSymboleVide(0,0);
	a3->filsGauche=a1;
	a3->filsDroit=a2;
	a3->occurrence=a1->occurrence+a2->occurrence;
	return a3;
}

void print_Abr(ArbreSymbole* a, int l) {
	int i, j;
	if (a != NULL) {
		print_Abr(a->filsDroit, l + 1);
		for (j = 0; j < l; j++)
			printf("\t");
		printf(" %d, %d \n", a->valeur, a->taille);
		print_Abr(a->filsGauche, l + 1);
	}
	return;
}