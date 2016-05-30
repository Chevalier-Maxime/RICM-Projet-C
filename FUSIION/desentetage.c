#include <stdio.h>
#include <stdlib.h>
#include "desentetage.h"
#include "sdata.h"

entete * decrypterentete(FILE* fichier)
{
	char c;
	int courant = 0,nbSymb,i,k;
	courant=fgetc(fichier);
	if(courant!='1') 
	{
		printf("identifiant non reconnu\n");
		exit(0);
	}
	courant=fgetc(fichier);
	if(courant!='8') 
	{
		printf("identifiant non reconnu\n");
		exit(0);
	}
	courant=fgetc(fichier);
	if(courant!='1') 
	{
		printf("identifiant non reconnu\n");
		exit(0);
	}
	courant=fgetc(fichier);
	if(courant!='5') 
	{
		printf("identifiant non reconnu\n");
		exit(0);
	}
	courant=fgetc(fichier);
	nbSymb=courant-48;
	unsigned char tabS[256];
	int tabI[256];
	i=0;
	while(i!=nbSymb)
	{
		c=fgetc(fichier);
		printf("%c\n",c);
		tabS[i]=c;
		k = calcule(fichier);
		printf("%d\n",k);
		tabI[i]=k;
		i++;
		printf("finboucle\n");
	}
	entete * ent =creerEntete(nbSymb, tabI,tabS);
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
