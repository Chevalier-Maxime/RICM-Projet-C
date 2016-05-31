#include <stdio.h>
#include <stdlib.h>

void ecriture(int i,FILE* fichierPretraite,int courant)
{
	char c = (char) courant;
	while(i!=0)
			{
				if(i>0 && i<=255)
					{
						fprintf(fichierPretraite,"%d",i); 
						fprintf(fichierPretraite,"%c",'S');
						fprintf(fichierPretraite,"%c",'S');
						i=0;
					}
				if(i>255 && i<=257)				
					{
						fprintf(fichierPretraite,"%d",130);
						fprintf(fichierPretraite,"%c",'S');
						fprintf(fichierPretraite,"%c",'S');
						fprintf(fichierPretraite,"%c",c);
						fprintf(fichierPretraite,"%c",c);
						i=i-132;
					}
				if(i>257)
					{
						fprintf(fichierPretraite,"%d",255);
						fprintf(fichierPretraite,"%c",'S');
						fprintf(fichierPretraite,"%c",'S');
						fprintf(fichierPretraite,"%c",c);
						fprintf(fichierPretraite,"%c",c);
						i=i-255;
					}
  			}	
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

void pretraiter( FILE* fichier, FILE* fichierPretraite)
{
	unsigned char octetCourant ;
	unsigned char octetPrecedent;
	unsigned char nbRepetition;
	int res;

	//#TODO Test pour tres petit fichier
	fread(&octetPrecedent, sizeof(unsigned char), 1, fichier);
	fwrite(&octetPrecedent, sizeof(unsigned char), 1, fichierPretraite);
	res = fread(&octetCourant, sizeof(unsigned char), 1, fichier);
	fwrite(&octetCourant, sizeof(unsigned char), 1, fichierPretraite);

	while (res)
	{
		if (octetCourant == octetPrecedent) //On a deux fois le meme symbole d'affilée
		{
			nbRepetition = 0;
			fread(&octetCourant, sizeof(unsigned char), 1, fichier);
			while (octetCourant==octetPrecedent && nbRepetition<256 && res)
			{
				nbRepetition++;
				res = fread(&octetCourant, sizeof(unsigned char), 1, fichier);
			}
			fwrite(&nbRepetition, sizeof(unsigned char), 1, fichierPretraite);
		}
		octetPrecedent = octetCourant;
		res = fread(&octetCourant, sizeof(unsigned char), 1, fichier);
		fwrite(&octetCourant, sizeof(unsigned char), 1, fichierPretraite);
	}

	/*int courant=0,suivant=0, i=0;
	char c;

	if (fichier != NULL)
    {
			courant = fgetc(fichier);

			while (!testfinCaractere(courant) && !testerreurCaractere(courant))
        {	
						c=(char)courant;
						fprintf(fichierPretraite,"%c",c); 
						suivant = fgetc(fichier);
						if(sontIdentique(courant,suivant) && !testfinCaractere(suivant) && !testerreurCaractere(suivant))
							{
								c=(char)suivant;
								fprintf(fichierPretraite,"%c",c);
								suivant=fgetc(fichier);
								while(sontIdentique(courant,suivant) && !testfinCaractere(suivant) && !testerreurCaractere(suivant))
									{
										i++;
										suivant = fgetc(fichier);
									}
								if(i==0)
									{
										fprintf(fichierPretraite,"%d",0);
										fprintf(fichierPretraite,"%c",'S');
										fprintf(fichierPretraite,"%c",'S');
									}
								ecriture(i,fichierPretraite,courant);
								
								i=0;
							}
							else
							{
								fprintf(fichierPretraite,"%c",'S');
								fprintf(fichierPretraite,"%c",'S');
							}
						courant=suivant;
				}
    }
else printf("Fichier vide");
    return ;*/
}


