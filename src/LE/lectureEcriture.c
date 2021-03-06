#include "lectureEcriture.h"
#include <stdlib.h>
#include <stdio.h>

#define taille_nom_fichier 256
FILE * fichierACompresser; 
FILE * fichierTemporaire;
FILE * fichierCompresse;
FILE * fichierADecompresser;

//~ void lireFichier(donnees * d)
//~ {
    //~ FILE* fichier = NULL;

	//~ //Demander chemin d'acces
	 //~ printf("Quel est votre nom de fichier?  ");
		//~ scanf("%s",nomFichier);
	//~ //tester si il est valide
	//~ //si non, redemander
	
    //~ fichier = fopen("sdata.h", "r+");

    //~ if (fichier != NULL)
    //~ {
       //~ // lire et �crire dans le fichier
        
        
        
        //~ fclose(fichier); 
    //~ }
    //~ else
    //~ {
        
        //~ printf("Impossible d'ouvrir le fichier ");
    //~ }
//~ }

void realisationCompression(ArbreSymbole * arbre)
{
}

/**
 * Permet de lire octet par octet dans un fichier
 * @param fichier : Le fichier � lire, doit �tre ouvert
 * @param symbole : l'octet lu
 * @return : 1 si la lecture s'est bien pass�, 0 sinon
 **/
int lectureOctet(FILE * fichier, unsigned char* symbole) //#TODO Je suis pas sur que ce soit utile...
{
	if(fichier==NULL) return 0;
	
	int caractereCourant = fgetc(fichier);
	*symbole = caractereCourant;
	return caractereCourant;
}


typedef struct dernierOctet{
	char dernierOctetLu;
	int positionCourante;
} dernierOctet;

dernierOctet * dL;
unsigned char MASK = 1;

/**
 * Permet de lire bit par bit dans un fichier
 * @param fichier le fichier ouvert dans lequel lire
 * @param symbole le digit lu mis dans un char.
 * @return : 1 si la lecture s'est bien pass�, 0 sinon
 **/ 
int lectureBit(FILE * fichier, unsigned char* symbole)
{
	if(fichier==NULL) return 0;
	if(dL==NULL)
	{
		 dL = malloc(sizeof(dernierOctet));
		 dL->positionCourante = 8;
	}
	if(dL->positionCourante==8)
	{
		dL->dernierOctetLu = fgetc(fichier);
		if(dL->dernierOctetLu==EOF) return 0;
		dL->positionCourante=0;
	}
	*symbole = ((dL->dernierOctetLu)&(MASK<<dL->positionCourante))>>dL->positionCourante;
	dL->positionCourante+=1;
	return 1;
}

/**
 * Permet d'ecrire octet par octet dans un fichier
 * @param fichier : Le fichier o� �crire, doit �tre ouvert
 * @param symbole : l'octet � �crire
 * @return : 1 si l'�criture s'est bien pass�, 0 sinon
 **/
int ecritureOctet(FILE * fichier, unsigned char* symbole)
{
	
	return 0;	
}


dernierOctet * dE;
/**
 * Permet d'ecrire octet par octet dans un fichier
 * @param fichier : Le fichier o� �crire, doit �tre ouvert
 * @param symbole : le digit � �crire
 * @return : 1 si l'�criture s'est bien pass�, 0 sinon
 **/
int ecritureBit(FILE * fichier, unsigned char* symbole)
{
	if(fichier==NULL) return 0;
	if(dE==NULL)
	{
		 dE = malloc(sizeof(dernierOctet));
		 dE->positionCourante = 0;
		 dE->positionCourante = 0;
	}
	if(dE->positionCourante==8)
	{
		int resultat = fputs(&(dE->dernierOctetLu),fichier);
		if(resultat == EOF) return 0;
		dE->positionCourante=0;
		dE->positionCourante = 0;
	}
	dE->dernierOctetLu = ((*symbole & MASK)<<dE->positionCourante) | dE->dernierOctetLu;
	dE->positionCourante++;
	return 1;
}

int main(void)
{
	//Test lecture
	FILE * fichier;
	char chemin[] = "./testLecture.txt";
	unsigned char caractereActuel;
	int a;
	fichier = fopen(chemin, "r+");
	if (fichier != NULL)
    {
        // Boucle de lecture des caract�res un � un
        do
        {
             a = lectureBit(fichier, &caractereActuel); // On lit le caract�re
            printf("%c", caractereActuel); // On l'affiche
        } while (a != EOF); // On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)
        fclose(fichier);
    }
    return 0;
}
