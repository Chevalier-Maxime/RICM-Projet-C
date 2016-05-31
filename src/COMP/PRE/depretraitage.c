#include <stdio.h>
#include <stdlib.h>
#include "depretraitage.h"

void depretraiter( FILE* fichier, FILE* fichierDepretraite)

{
int courant=0,precedent=0,k;

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
    return ;
}

int testerreurCaractere(int courant)
{
	if(courant==-1) return 1;
	else return 0;
}

int testfinCaractere(int courant)
{
	if(courant==EOF) return 1;
	else return 0;
}

int sontIdentique(int courant, int suivant)
{
	if(courant==suivant) return 1;
	else return 0;
}
