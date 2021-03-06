#include "sdata.h"
#include  <stdlib.h>

void creerArbreBinaire(int hauteur, ArbreEntier * arbre)
{
	if(hauteur ==0){
		arbre->valeur = 0;
		arbre->filsDroit = NULL;
		arbre->filsGauche = NULL;
		return;
	}
	(arbre)->filsDroit = malloc(sizeof(ArbreEntier));
	(arbre)->filsGauche = malloc(sizeof(ArbreEntier));
	creerArbreBinaire(hauteur-1, arbre->filsDroit);
	creerArbreBinaire(hauteur-1, arbre->filsGauche);
}

ArbreEntier * creerArbreEntierVide(int valeur)
{
	ArbreEntier * a = malloc(sizeof(ArbreEntier));
	a->valeur = valeur;
	return a;
}

int nombreOccurance(ArbreEntier * arbre, char symbole)
{
	char lu;
	ArbreEntier * noeudCourrant = arbre;
	ArbreEntier * noeudPrecedent = NULL;
	int indiceSymbole = 0;
	char masque = 1;
	while(noeudCourrant!=NULL)
	{
		lu = lu | (symbole&(!(masque<<indiceSymbole)));
		noeudPrecedent = noeudCourrant;
		if (((symbole&(!(masque<<indiceSymbole)))>>indiceSymbole)==0)
		{
			noeudCourrant = noeudCourrant->filsGauche;
		}else{
			
			noeudCourrant = noeudCourrant->filsGauche;
		}
	}
	if(lu==symbole) return noeudPrecedent->valeur;
	
	return -1;
}


int estFeuilleE(ArbreEntier * arbre)
{
	if((arbre->filsDroit==NULL)&&(arbre->filsGauche==NULL)) return 1;
	return 0;
}

int estFeuilleS(ArbreSymbole* arbre)
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

ArbreSymbole * creerArbreSymboleVide(char valeur)
{	
	ArbreSymbole * a = malloc(sizeof(ArbreSymbole));
	a->valeur = valeur;
	a->filsDroit = NULL;
	a->filsGauche = NULL;
	return a;
}

ArbreSymbole * insererfils(ArbreSymbole * arbre,ArbreSymbole * g,ArbreSymbole * d)
{
	arbre->filsDroit=d;
	arbre->filsGauche=g;
	return arbre;
}

entete * creerEntete(int nbSymb, int tabI[256], unsigned char tabS[256])
{
	entete * res = malloc(sizeof(entete));
	res->nbSymboles=nbSymb;
	int i;
	for ( i = 0; i <256; i++)
	{
		res->TailleS[i] = tabI[i];
		res->Symbole[i] = tabS[i];
	}
	
	return res;
}
