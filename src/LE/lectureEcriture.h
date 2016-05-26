#ifndef LECTUREECRITURE_H
	#define LECTUREECRITURE_H
	#include "../SDATA/sdata.h"
	#include <stdio.h>
	
	extern FILE * fichierACompresser;
	extern FILE * fichierTemporaire;
	extern FILE * fichierCompresse;
	extern FILE * fichierADecompresser;
	
	void lireFichier(donnees * d);
	void realisationCompression(ArbreSymbole * arbre);
	int lectureOctet(FILE * fichier, unsigned char* symbole);
	int lectureBit(FILE * fichier, unsigned char* symbole);
	int ecritureOctet(FILE * fichier, unsigned char* symbole);
	int ecritureBit(FILE * fichier, unsigned char* symbole);
#endif


