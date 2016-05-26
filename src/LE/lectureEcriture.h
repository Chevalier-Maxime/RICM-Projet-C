#ifndef LECTUREECRITURE_H
	#define LECTUREECRITURE_H
	#include "sdata.h"
	
	extern FILE * fichierACompresser;
	extern FILE * fichierTemporaire;
	extern FILE * fichierCompresse;
	extern FILE * fichierADecompresser;
	
	void lireFichier(donnees * d);
	void realisationCompression(Arbre * arbre);
	int lectureOctet(FILE * fichier, char* symbole);
	int lectureBit(FILE * fichier, char* symbole);
	int ecritureOctet(FILE * fichier, char* symbole);
	int ecritureBit(FILE * fichier, char* symbole);
#endif


