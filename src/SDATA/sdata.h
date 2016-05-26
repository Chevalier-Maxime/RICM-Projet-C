#define TAILLE_SEQUENCE_DEBUT //#TODO a definir
#define SEQUENCE_DEBUT //#TODO a definir

typedef struct donnees
{
	Arbre* racineArbreBinaire;
	int nbSymboles;
	int Lmax; //donné
} donnees;

typedef struct Arbre
{
	Arbre* filsGauche;
	Arbre* filsDroit;
	int valeur;
} Arbre;

typedef struct entete
{
	int nbSymboles;
	Arbre* arbreCanonique;
	int nbPadding;
	int tailleEntete;
} entete;

union octet{
	char symbole;
	//#TODO a voir...
}

void creerArbreBinaire(int hauteur, Arbre * arbre);
int nombreOccurance(Arbre * arbre, char symbole);
int estFeuille(Arbre * arbre);
Arbre * ajouterNoeudParent(Arbre * fils, char dirrection); 

