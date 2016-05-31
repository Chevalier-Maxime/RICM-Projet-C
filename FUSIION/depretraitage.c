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
	fwrite(&octetCourant, sizeof(unsigned char), 1, fichierDepretraite);

	while (res)
	{
		if (octetCourant == octetPrecedent) //On a deux fois le meme symbole d'affilée
		{
			//Le caractere suivant est un nombre de repetition
			fread(&nbRepetition, sizeof(unsigned char), 1, fichier);
			for ( i = 0; i < nbRepetition; i++)
			{
				//On recopie
				fwrite(&octetCourant, sizeof(unsigned char), 1, fichierDepretraite);
			}
			//fread(&octetCourant, sizeof(unsigned char), 1, fichier);
		}
		octetPrecedent = octetCourant;
		res = fread(&octetCourant, sizeof(unsigned char), 1, fichier);
		fwrite(&octetCourant, sizeof(unsigned char), 1, fichierDepretraite);
	}



/*int courant=0,precedent=0,k;

char c;

 if (fichier != NULL)
    {
			courant = fgetc(fichier);

			while (!testfinCaractere(courant) && !testerreurCaractere(courant))
        {	
						precedent = courant;
						c=(char)precedent;
						fprintf(fichierDepretraite,"%c",c); 
						courant = fgetc(fichier);
						if(sontIdentique(precedent,courant) && !testfinCaractere(courant) && !testerreurCaractere(courant))
							{
								k=0;
								c=(char)courant;
								fprintf(fichierDepretraite,"%c",c);
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
								while(k!=0)
									{
										fprintf(fichierDepretraite,"%c",c);
										k--;
									}
								courant = fgetc(fichier);
							}
						else
							{
								precedent = courant;
								courant= fgetc(fichier);
								if(courant==83 && precedent==83)
									{
										courant= fgetc(fichier);
									}
									else
										{
											printf("erreur\n");
											exit(0);
										}
							}
				}
    }
else printf("Fichier vide");
    return ;*/
}


