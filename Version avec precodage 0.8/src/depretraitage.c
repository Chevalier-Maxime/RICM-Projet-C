#include <stdio.h>
#include <stdlib.h>
#include "depretraitage.h"
#include "pretraitement.h"

void depretraiter( FILE* fichier, FILE* fichierDepretraite)
{

	unsigned char octetCourant;
	unsigned char octetPrecedent;
	unsigned char nbRepetition;
	int res;
	int i;

	//#TODO Test pour tres petit fichier
	fread(&octetPrecedent, sizeof(unsigned char), 1, fichier);
	fwrite(&octetPrecedent, sizeof(unsigned char), 1, fichierDepretraite);
	res = fread(&octetCourant, sizeof(unsigned char), 1, fichier);


	while (res)
	{
		if (octetCourant == octetPrecedent) //On a deux fois le meme symbole d'affilée
		{
			fwrite(&octetCourant, sizeof(unsigned char), 1, fichierDepretraite);
			//Le caractere suivant est un nombre de repetition
			fread(&nbRepetition, sizeof(unsigned char), 1, fichier);
			for (i = 0; i < nbRepetition; i++)
			{
				//On recopie
				fwrite(&octetCourant, sizeof(unsigned char), 1, fichierDepretraite);
			}
			fread(&octetCourant, sizeof(unsigned char), 1, fichier);
		}
		if (res)
		{
			octetPrecedent = octetCourant;
			res = fread(&octetCourant, sizeof(unsigned char), 1, fichier);
			fwrite(&octetPrecedent, sizeof(unsigned char), 1, fichierDepretraite);
		}
	}
}
