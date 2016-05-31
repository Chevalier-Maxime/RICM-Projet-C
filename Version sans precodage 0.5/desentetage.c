#include <stdio.h>
#include <stdlib.h>
#include "desentetage.h"
#include "sdata.h"
#include <string.h>

entete * decrypterentete(FILE* fichier)
{
	char identifiant[4];
	int nbSymb,i,nbSDifferents;
	
	fread(identifiant, sizeof(char), 4, fichier);
	if (!strcmp(identifiant, "1815")) {
		printf("fichier non compilé par nos soins !\n"); exit(0);
	}
	
	fread(&nbSymb, sizeof(int), 1, fichier); //On lit le nombre de symboles
	fread(&nbSDifferents, sizeof(int), 1, fichier); //On lit le nombre de symboles

	unsigned char tabS[256];
	int tabI[256];
	i=0;
	while(i<nbSDifferents)
	{
		fread(&(tabS[i]), sizeof(char), 1, fichier); //On lit le symbole
		fread(&(tabI[i]), sizeof(int), 1, fichier); //On lit la profondeur
		i++;
	}
	entete * ent =creerEntete(nbSymb, nbSDifferents, tabI,tabS);
	return ent;
}
		
int calcule(FILE* fichier)
{
	int k,courant,precedent;
	k=0;
	courant = fgetc(fichier);
	precedent = courant;
	courant = fgetc(fichier);
	if(courant==83)
		{
			k=10*k+(precedent-48);
			precedent = courant;
			courant = fgetc(fichier);
		}
	else
		{
			k=10*k+(precedent-48);
			precedent = courant;
			courant = fgetc(fichier);
			if(courant==83)
			{
				k=10*k+(precedent-48);
				precedent = courant;
				courant = fgetc(fichier);
			}
			else
			{
				k=10*k+(precedent-48);
				precedent = courant;
				courant = fgetc(fichier);
				k=10*k+(precedent-48);
				precedent = courant;
				courant = fgetc(fichier);
			}
		}
return k;
}
