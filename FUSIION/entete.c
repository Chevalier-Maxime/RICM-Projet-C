#include <stdio.h>
#include <stdlib.h>
#include "entete.h"
#include "sdata.h"

void ecrireentete(entete * ent,FILE* fichieraenteter )
{
	int n,i,k;
	char c;
	n=ent->nbSymboles;

	fwrite("1815", sizeof(char), 4, fichieraenteter); //On place un identifiant au debut du fichier.
	fwrite(&n, sizeof(int), 1, fichieraenteter); //On met le nombre de symboles dans le fichier
	fwrite(&(ent->nbSymbolesDifferents), sizeof(int), 1, fichieraenteter); //On met le nombre de symboles differents dans le fichier

	unsigned char * symbole = ent->Symbole;
	int* profondeur = ent->TailleS;
	i=0;
	while(i<n && profondeur[i]!=0)
	{
		c = symbole[i];
		k = profondeur[i];
		fwrite(&c, sizeof(char), 1, fichieraenteter); //symbole
		fwrite(&k, sizeof(int), 1, fichieraenteter); //profondeur du symbole
		i++;
	}
	return;
}
	
