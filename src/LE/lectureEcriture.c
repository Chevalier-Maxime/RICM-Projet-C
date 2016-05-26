#include "lectureEcriture.h"
#include "sdata.h"
#include <stdlib.h>
#include <stdio.h>

FILE * fichierACompresser;
FILE * fichierTemporaire;
FILE * fichierCompresse;
FILE * fichierADecompresser;

void lireFichier(donnees * d)
{
    FILE* fichier = NULL;

    fichier = fopen("sdata.h", "r+");

    if (fichier != NULL)
    {
       // lire et écrire dans le fichier
        
        
        
        fclose(fichier); 
    }
    else
    {
        
        printf("Impossible d'ouvrir le fichier ");
    }
}

void realisationCompression(Arbre * arbre)
{
	//#TODO
}
int lectureOctet(FILE * fichier, char* symbole)
{
	
}
int lectureBit(FILE * fichier, char* symbole)
{
}
int ecritureOctet(FILE * fichier, char* symbole)
{
}
int ecritureBit(FILE * fichier, char* symbole)
{
}
