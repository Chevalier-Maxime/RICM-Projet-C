#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "sdata.h"

#define NOMBRE_SYMBOLES 256
#define TAILLE_LIMITE_MERGE 4096

//Structure d'arbre canonique sous forme de tableaux
typedef struct Canonique{
	unsigned char Symbole[NOMBRE_SYMBOLES]; //Symbole sur un octet -> 256 possibilités
	int TailleS[NOMBRE_SYMBOLES]; //Taille du symbole
	int Taille; //Taille des tableaux (0<=Taille<=256)
}Canonique;

//Structure de Huffman, contient les symboles, leur occurrences respectives et leur tailles
typedef struct TabHuff{
	unsigned char Symbole[NOMBRE_SYMBOLES];
	int Occurrence[NOMBRE_SYMBOLES];
	int TailleS[NOMBRE_SYMBOLES];
	int Taille;
}TabHuff;

//Structure de Package Merge, s'appuie en partie sur TabHuff
typedef struct TabMerge{
	liste* Package[TAILLE_LIMITE_MERGE]; //Tableau de listes pour les packages créés
	int PoidsP[TAILLE_LIMITE_MERGE]; //Le poids de chacunes des listes (somme de occurrences2 associées aux symboles)
	liste* Merge[TAILLE_LIMITE_MERGE]; //Tableau de listes fusions de TabHuff.Symbole et Package
	int PoidsM[TAILLE_LIMITE_MERGE]; //Le poids assoicé
	int Occurrence2[NOMBRE_SYMBOLES]; //Les occurrences de chacuns des symboles selon Package (symboles rangés dans le même ordre que TabHuff)
	int TailleP; //Taille de Package
	int TailleM; //Taille de Merge
}TabMerge;

//Structure de tableau d'arbres
typedef struct TabArb{
	ArbreSymbole* a[NOMBRE_SYMBOLES]; //Un arbre par symbole
	int Taille; //Taille du tableau
}TabArb;

//Associe à chaque symbole sur 8bits son code de Huffman et sa taille
typedef struct HuffSymb {
	unsigned char S[NOMBRE_SYMBOLES]; //Symbole de base sur 8bits
	int H[NOMBRE_SYMBOLES]; //Symbole de Huffman associé (limité à 32bits)
	unsigned char T[NOMBRE_SYMBOLES]; //Taille du symbole de Huffman associé
	int Taille; //Nombre de symboles, taille des tableaux
}HuffSymb;

//Initialise la structure donnée en paramètre à 0 
void initTableau(TabHuff* t);

//Complète la structure de tableaux TabHuff d'après un arbre de symboles
void ecritTableau(ArbreSymbole* a, TabHuff* t, unsigned char Longueur, unsigned char Symbole, unsigned char Indice);

//Tri par insertion puuis élimination des symboles dont l'occurrence est nulle
void TriArbreTableau(ArbreSymbole* a, TabHuff* t);

//Renvoie 1 si LmaxOpti du code de Huffman dépasse Lmax imposé
int TestMerge(TabHuff* TH, donnees d);

//Parcourt l'arbre de Huffman et remplit HuffSymb
void SymboleHuffman(ArbreSymbole* a, HuffSymb * HS, unsigned char Valeur);

//Complète un arbre de Huffman inversé selon les valeurs de HuffSymb associées
//Un arbre de Huffman inversé est de taille fixe (8) pour permettre un parcours facile vers tous les symboles possibles (256)
//La feuille atteinte selon un symbole sur 8bits possède le code de Huffman associé
//Sera utilisé lors de la lecture du fichier à compresser
void RemplitArbreHuffman(ArbreEntier* a, unsigned char symboleOrigine, int symboleHuffman, unsigned char Taille);

//Réalise l'arbre de Huffman inversé
ArbreEntier* ConversionArbre(ArbreSymbole * a);

//Complète le champ TailleS de TH associé au symbole
void AjoutTailleTH(unsigned char Symbole, TabHuff* TH, int Taille);

//Complète la taille des symboles dans l'arbre et appelle AjoutTailleTH
void TailleSymbole(ArbreSymbole* a, int Taille, TabHuff* TH);

//Réalise le codage de Huffman
ArbreEntier* Huffman(donnees d, TabHuff* Tab);


void InitPM(TabMerge* TM, TabHuff* TH);

liste* Concat2Listes(liste* L1, liste* L2);

void MergeAjout(TabHuff* TH, TabMerge* TM);

void AjoutSymbole(unsigned char Symbole, TabHuff* TH, TabMerge* TM);
ArbreSymbole* ConstruireArbre(TabHuff* TH, TabMerge* TM, int Prof, int Indice);
ArbreSymbole* ArbreMerge(TabHuff* TH, TabMerge* TM);

ArbreEntier* Merge(donnees d, TabHuff* TH);

//Structure canonique construite selon TabHuff sera envoyé au programme principal pour la réalisation de l'entête
void RealCanonique(Canonique* C, TabHuff* TH);

ArbreEntier * Compression(donnees d, Canonique* C);

#endif // !COMPRESSION_H
