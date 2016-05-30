#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "sdata.h"

typedef struct TabHuff{
	unsigned char Symbole[256];
	int Occurrence[256];
	int Occurrence2[256];
	int TailleS[256];
	int Taille;
}TabHuff;

typedef struct TabMerge{
	liste* Package[2048];
	int PoidsP[2048];
	liste* Merge[2048];
	int PoidsM[2048];
	int TailleP;
	int TailleM;
}TabMerge;

typedef struct TabArb{
	ArbreSymbole* a[256];
	int Taille;
}TabArb;

typedef struct HuffSymb {
	unsigned char S[256];
	int H[256];
	unsigned char T[256];
	int Taille;
}HuffSymb;

void initTableau(TabHuff* t);

void ecritTableau(ArbreSymbole* a, TabHuff* t, unsigned char Longueur, unsigned char Symbole, unsigned char Indice);

//Tri par insertion
void TriArbreTableau(ArbreSymbole* a, TabHuff* t);
int TestMerge(TabHuff* TH, donnees d);

void SymboleHuffman(ArbreSymbole* a, HuffSymb * HS, unsigned char Valeur);
void RemplitArbreHuffman(ArbreEntier* a, unsigned char symboleOrigine, int symboleHuffman, unsigned char Taille);

ArbreEntier* ConversionArbre(ArbreSymbole * a);
void AjoutTailleTH(unsigned char Symbole, TabHuff* TH, int Taille);

void TailleSymbole(ArbreSymbole* a, int Taille, TabHuff* TH);


ArbreEntier* Huffman(donnees d, TabHuff* Tab);
void InitPM(TabMerge* TM);

liste* Concat2Listes(liste* L1, liste* L2);

void MergeAjout(TabHuff* TH, TabMerge* TM);

void AjoutSymbole(unsigned char Symbole, TabHuff* TH);
ArbreSymbole* ConstruireArbre(TabHuff* TH, int Prof, int Indice);
ArbreSymbole* ArbreMerge(TabHuff* TH);

ArbreEntier* Merge(donnees d, TabHuff* TH);

ArbreEntier * Compression(donnees d, TabHuff Tab);

#endif // !COMPRESSION_H
