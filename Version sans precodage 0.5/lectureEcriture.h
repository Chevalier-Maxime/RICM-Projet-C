#ifndef LECTUREECRITURE_H
	#define LECTUREECRITURE_H
	#include "sdata.h"
	#include <stdio.h>
	
	#define TAILLE_NOM_FICHIER 256
	#define NOM_FICHIER_TEMP "temp"
	#define NOM_FICHIER_COMP "fichierCompresse"
	#define NOM_FICHIER_DECOMP "fichierDecompresse"
	char nomFichierACompresser[TAILLE_NOM_FICHIER];
	char nomFichierCompresser[TAILLE_NOM_FICHIER];
	char nomFichierDecompresser[TAILLE_NOM_FICHIER];
	FILE * fichierACompresser;
	FILE * fichierTemporaire;
	FILE * fichierCompresse;
	//FILE * fichierADecompresser;
	FILE  * fichierDecompresse;


	extern FILE * fichierACompresser;
	extern FILE * fichierTemporaire;
	extern FILE * fichierCompresse;
	extern FILE * fichierADecompresser;
	
	void lireFichier();
	int lectureOctet(FILE * fichier, unsigned char* symbole);
	int lectureBit(FILE * fichier, unsigned char* symbole);
	int ecritureOctet(FILE * fichier, unsigned char* symbole);
	int ecritureBit(FILE * fichier, unsigned char* symbole);
	void remplirDonneeFichierASCII(donnees * d, FILE * fichierALire);
	int transcoderASCII(char c, ArbreEntier * a, FILE * fichierDestination);
	int realiserCompressionASCII(ArbreEntier * a, donnees * d, entete * e, FILE * fichierOrigine, FILE * fichierDestination);
	void realiserDecompressionASCII(ArbreSymbole * arbreCanonique, entete * e, FILE * fichierOrigine, FILE * fichierDestination);
#endif


