#include "lectureEcriture.h"
#include <stdlib.h>
#include <stdio.h>



void lireFichier()
{

	int dejaPasse = 0;
	int retester = 0;
	do {
		if (dejaPasse)
		{
			fprintf(stderr, "Ce fichier n'existe pas, pensez inclure l'extention si le fichier en poss�de une.\nPar exemple, tapez nomFichier.txt\nPensez egalement a noter le chemin d'acces.\n");
			printf("Essayer un autre fichier ? (1 = oui, 0 = non) ->  ");
			scanf("%d", &retester);
			if (!retester)
			{
				exit(0);
			}
		}
		printf("Quel est le chemin d'acces au fichier a compresser?  ");
		scanf("%s", nomFichierACompresser);
		fichierACompresser = fopen(nomFichierACompresser, "r+b");
		dejaPasse = 1;
	} while (fichierACompresser == NULL);
}

void remplirDonneeFichierASCII(donnees * d, FILE * fichierALire)
{
	if (fichierALire == NULL) return;
	int res;
	char c;
	do //FAIRE UNE PREMIERE FOIS AVANT DE RENTRER DANS LA BOUCLE, SI FICHIER VIDE, ICI CA MARCHE PAS
	{
		res = fgetc(fichierALire);
		c = res;
		ajouterOccurenceAbreSymbole(d->arbre, &c);
		d->nbSymboles++;
	} while (res != EOF);
}

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
	int taille;
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
		 dL->positionCourante = -1;
	}
	if(dL->positionCourante==-1)
	{
		int tailleLu = fread(&dL->dernierOctetLu, sizeof(char), 1, fichier);; //probleme de lecture binaire, faire avec fread
		if(tailleLu ==0) return 0;
		dL->positionCourante=7;
	}
	*symbole = ((dL->dernierOctetLu)&(MASK<<dL->positionCourante))>>dL->positionCourante;
	dL->positionCourante-=1;
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
		 dE->positionCourante = 7;
		 dE->dernierOctetLu = 0x0;
		 dE->taille = 0;
	}
	if(dE->positionCourante==-1)
	{
		int resultat = fwrite(&(dE->dernierOctetLu), sizeof(char), 1, fichier);
		if(resultat == EOF) return 0;
		dE->positionCourante=7;
		dE->dernierOctetLu = 0x0;
		dE->taille = 0;
	}
	dE->dernierOctetLu = ((*symbole & MASK)<<dE->positionCourante) | dE->dernierOctetLu; //-----------Modif /!\ : ((*symbole & MASK)<<dE->positionCourante) | dE->dernierOctetLu
	dE->positionCourante--;
	dE->taille++;
	return 1;
}

//ajouter retour taille
//#TODO BUG // PEUT PAS TEST A CAUSE DE TAILLE --->Demander fichiers � HUGO
int pousserEcritureBit(FILE * fichier)
{
	return fwrite(&(dE->dernierOctetLu), sizeof(char), 1, fichier);
}

int realiserCompressionASCII(ArbreEntier * a, donnees * d, entete * e, FILE * fichierOrigine, FILE * fichierDestination)
{
	int res, i;
	unsigned long int sommeEcriture = 0;
	char c;
	for (i = 0; i < d->nbSymboles; i++)
	{
		res = fgetc(fichierOrigine);
		c = res;
		sommeEcriture += transcoderASCII(c, a, fichierDestination);
	}
	//if (sommeEcriture % 8 != 0) 
	pousserEcritureBit(fichierDestination);
	return sommeEcriture % 8; //padding ajoute a la fin. On le sait que maintenant donc il va falloir modifier l'entete � la fin pour ecrire la taille du pading...
}


int transcoderASCII(char c, ArbreEntier * a, FILE * fichierDestination)
{
	ArbreEntier * noeudCourant;
	unsigned int MASK = 0x1;
	unsigned char bit;
	int bitCourant;
	noeudCourant = a;
	for (bitCourant = 7; bitCourant >= 0; bitCourant--)
	{
		bit = ((MASK << bitCourant)&c) >> bitCourant;
		if (bit == 0x1)
		{
			if (noeudCourant->filsDroit != NULL)
			{
				noeudCourant = noeudCourant->filsDroit;
			}
		}
		if (bit == 0x0){
			if (noeudCourant->filsGauche != NULL)
			{
				noeudCourant = noeudCourant->filsGauche;
			}
		}
	}
	if (estFeuilleEntier(noeudCourant)){
		int i;
		//if (noeudCourant->taille > 7) printf("lectureEcriture.c : taille symbole trop importante pour un char.");
		for (i = noeudCourant->taille-1; i >=0 ;i--)
		{
			bit = ((MASK << i)&noeudCourant->valeur) >> i;
			ecritureBit(fichierDestination, &bit);
		}
	}
	else
	{
		printf("lectureEcriture.c : transcoderASCII erreur\n"); exit(0);
	}
	return noeudCourant->taille;
}

void realiserDecompressionASCII(ArbreSymbole * arbreCanonique, entete * e, FILE * fichierOrigine, FILE * fichierDestination)
{
	unsigned int MASK = 0x1;
	unsigned char bit;
	ArbreSymbole * noeudCourant = arbreCanonique;
	int i=0;
	while (i<e->nbSymboles-1)
	{
		lectureBit(fichierOrigine,&bit); //PENSER A OUVRIR LE FICHIER QUELQUE PART en mode w+b
		if (bit == 0x1)
		{
			if (noeudCourant->filsDroit != NULL)
			{
				noeudCourant = noeudCourant->filsDroit;
			}
		}
		if (bit == 0x0) {
			if (noeudCourant->filsGauche != NULL)
			{
				noeudCourant = noeudCourant->filsGauche;
			}
		}
		if (estFeuille(noeudCourant))
		{
			fwrite(&noeudCourant->valeur, sizeof(char), 1, fichierDestination);
			i++;
			noeudCourant = arbreCanonique;
		}
	}
}

/*
int main(void)
{
		//Test lecture
	FILE * fichier;
	char chemin[] = "test.txt";
	unsigned char caractereActuel;
	int a;

	fichier = fopen(chemin, "w+b");
	int i;
	char c = 0xFF;
	char c2 = 0x00;
	//char tab[] = { 0x01,0x00,0x01,0x00 };
	for (i = 0; i < 8; i += 2)
	{
		ecritureBit(fichier, &c);
		ecritureBit(fichier, &c2);
	}
	pousserEcritureBit(fichier);
	fclose(fichier);

	fichier = fopen(chemin, "r+b");
	if (fichier != NULL)
    {
        // Boucle de lecture des caract�res un � un
        do
        {
             a = lectureBit(fichier, &caractereActuel); // On lit le caract�re
														// On l'affiche
			 if (caractereActuel == 0x1)
				 printf("1");
			 else if (caractereActuel == 0x0)
				 printf("0");
			 else printf("a");
        } while (a != 0); // On continue tant que fgetc n'a pas retourn� EOF (fin de fichier)
		fclose(fichier);
		
    }*/
	/*
	freopen("stdout.txt", "w", stdout);
	freopen("stderr.txt", "w", stdout);

	donnees * d = malloc(sizeof(donnees));
	TabHuff * tableauHuffman = malloc(sizeof(TabHuff));
	d->Lmax = 8;
	d->nbSymboles = 0;
	d->arbre = creerArbreSymboleVide(0, 0);
	//Met des 1 dans les noeuds, mettre des 0 --> demander HUGO
	creerArbreBinaire(8, d->arbre);
	lireFichier(d);
	ArbreEntier * a = Compression(*d, tableauHuffman);
	//print_Abr(a, 0);

	entete * e = malloc(sizeof(entete));
	e->nbSymboles = d->nbSymboles;
	int i;
	for (i = 0; i < 256; i++)
	{
		e->Symbole[i] = tableauHuffman->Symbole[i];
		e->TailleS[i] = tableauHuffman->TailleS[i];
	}

	

	int padding = realiserCompressionASCII(a, d, e);


	//AJOUTER NB SYMBOLES DANS ENTETE

	fichierCompresse = fopen(NOM_FICHIER_COMP, "r+b");
	fichierTemporaire = fopen(NOM_FICHIER_TEMP, "w+b");

	ArbreSymbole * arbreCanonique = Decompression(tableauHuffman->Symbole, tableauHuffman->TailleS, d->nbSymboles);
	printf("\n\n\n");
	print_Abr(arbreCanonique, 0);

	realiserDecompressionASCII(arbreCanonique, d, e);

	fclose(fichierTemporaire);
	fclose(fichierCompresse);

	//faire depretraitement
	fichierTemporaire = fopen(NOM_FICHIER_TEMP, "r");
	fichierDecompresse = fopen(NOM_FICHIER_DECOMP, "w+b");
	depretraiter(fichierTemporaire, fichierDecompresse);
	fclose(fichierTemporaire);
	fclose(fichierDecompresse);

	return 0;
}*/
