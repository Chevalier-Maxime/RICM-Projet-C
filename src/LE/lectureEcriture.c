#include "lectureEcriture.h"
#include "sdata.h"
#include <stdlib.h>
#include <stdio.h>

define taille_nom_fichier 256
FILE * fichierACompresser;
FILE * fichierTemporaire;
FILE * fichierCompresse;
FILE * fichierADecompresser;

void lireFichier(donnees * d)
{
    FILE* fichier = NULL;

	//Demander chemin d'acces
	 printf("Quel est votre nom de fichier?  ");
		scanf("%s",nomFichier);
	//tester si il est valide
	//si non, redemander
	
    fichier = fopen("sdata.h", "r+");

    if (fichier != NULL)
    {
       // lire et �crire dans le fichier
        
        
        
        fclose(fichier); 
    }
    else
    {
        
        printf("Impossible d'ouvrir le fichier ");
    }
}

void realisationCompression(Arbre * arbre)
{
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
