#include <stdio.h>
#include <stdlib.h>

#define TAILLE_SEQUENCE_DEBUT 1//#TODO a definir
#define SEQUENCE_DEBUT 3//#TODO a definir


#ifndef SDATA_H
#define SDATA_H

typedef struct ArbreEntier
{
	struct ArbreEntier* filsGauche;
	struct ArbreEntier* filsDroit;
	int valeur;
} ArbreEntier;

typedef struct ArbreSymbole
{
	struct ArbreSymbole* filsGauche;
	struct ArbreSymbole* filsDroit;
	char valeur;
} ArbreSymbole;

typedef struct donnees
{
	ArbreEntier* racineArbreBinaire;
	int nbSymboles;
	int Lmax; //donné
} donnees;

typedef struct entete
{
	int nbSymboles;
	int* tabI;
	char* tabS;
} entete;

union octet{
	char symbole;
	//#TODO a voir...
};

void creerArbreBinaire(int hauteur, ArbreEntier * arbre);
int nombreOccurance(ArbreEntier * arbre, char symbole);
int estFeuilleE(ArbreEntier * arbre);
int estFeuilleS(ArbreSymbole * arbre);
ArbreEntier * ajouterNoeudParentEntier(ArbreEntier * fils, char dirrection);
ArbreEntier * creerArbreEntierVide(int valeur);

ArbreSymbole * creerArbreSymboleVide(char valeur);
ArbreSymbole * insererfils(ArbreSymbole * arbre,ArbreSymbole * g,ArbreSymbole * d);

entete * creerEntete(int nbSymb, int* tabI, char* tabS);


#endif
