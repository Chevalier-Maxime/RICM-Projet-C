#include "sdata.h"

void creerArbreBinaire(int hauteur, Arbre * arbre)
{
	if(hauteur ==0){
		arbre->valeur = 0;
		arbre->filsDroi = NULL;
		arbre->filsGauche = NULL;
		return;
	}
	(arbre)->filsDroit = malloc(sizeof(Arbre));
	(arbre)->filsGauche = malloc(sizeof(Arbre));
	creerArbreBinaire(hauteur-1, arbre->filsDroit);
	creerArbreBinaire(hauteur-1, arbre->filsGauche);
}

int nombreOccurance(Arbre * arbre, char symbole)
{
	char lu;
	Arbre * noeudCourrant = arbre;
	Arbre * noeudPrecedent = NULL;
	int indiceSymbole = 0;
	char masque = 1;
	while(noeudCourrant!=NULL)
	{
		lu = lu | (symbole&(!(masque<<indiceSymbole));
		noeudPrecedent = noeudCourrant;
		if (((symbole&(!(masque<<indiceSymbole)))>>indiceSymbole)==0)
		{
			noeudCourrant = noeudCourrant->filsGauche;
		}else{
			
			noeudCourrant = noeudCourrant->filsGauche;
		}
	}
	if(lu==symbole) return noeudPrecedent.valeur;
	
	return -1;
}


int estFeuille(Arbre * arbre)
{
	if((arbre->filsDroit==NULL)&&(arbre->filsGauche==NULL)) return 1;
	return 0;
}


