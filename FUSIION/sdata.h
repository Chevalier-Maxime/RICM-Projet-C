#ifndef SDATA_H
#define SDATA_H
#define TAILLE_SEQUENCE_DEBUT //#TODO a definir
#define SEQUENCE_DEBUT //#TODO a definir


typedef struct ArbreEntier
{
	struct ArbreEntier* filsGauche;
	struct ArbreEntier* filsDroit;
	int valeur;
	int occurrence;
	int taille;
} ArbreEntier;

typedef struct ArbreSymbole
{
	struct ArbreSymbole* filsGauche;
	struct ArbreSymbole* filsDroit;
	unsigned char valeur;
	int occurrence;
	int taille;
} ArbreSymbole;

typedef struct donnees
{
	ArbreSymbole* arbre; // -----------------Changé arbre pour HUGO
	int nbSymboles;
	int Lmax; //donné
} donnees;

typedef struct liste
{
	struct liste* Suivant;
	char valeur;
} liste;



typedef struct entete
{
	int nbSymboles;
	ArbreEntier* arbreCanonique;
	int nbPadding;
	int tailleEntete;
} entete;

union octet{
	char symbole;
	//#TODO a voir...
};



int Puis2(int Valeur);
int ioc(unsigned char c);

void creerArbreBinaire(int hauteur, ArbreSymbole * arbre);
void creerArbreBinaireEntier(int hauteur, ArbreEntier * arbre);

int nombreOccurrence(ArbreEntier * arbre, unsigned char symbole);

int estFeuille(ArbreSymbole * arbre);
int estFeuilleEntier(ArbreEntier * arbre);

ArbreEntier * ajouterNoeudParentEntier(ArbreEntier * fils, char dirrection);
ArbreEntier * creerArbreEntierVide(int valeur, int occurrence);

ArbreSymbole * creerArbreSymboleVide(char valeur, int occurrence);
ArbreEntier * ajout2Arbres(ArbreEntier * a, ArbreEntier * a2);
void ajouterOccurenceAbreSymbole(ArbreSymbole * a, char * symbole);

ArbreSymbole * ajout2ArbresS(ArbreSymbole * a, ArbreSymbole * a2);

void print_Abr(ArbreSymbole* a, int l);
#endif // SDATA_H