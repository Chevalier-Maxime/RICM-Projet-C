#define TAILLE_SEQUENCE_DEBUT //#TODO a definir
#define SEQUENCE_DEBUT //#TODO a definir



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
	ArbreEntier* arbreCanonique;
	int nbPadding;
	int tailleEntete;
} entete;

union octet{
	char symbole;
	//#TODO a voir...
};

void creerArbreBinaire(int hauteur, ArbreEntier * arbre);
int nombreOccurance(ArbreEntier * arbre, char symbole);
int estFeuille(ArbreEntier * arbre);
ArbreEntier * ajouterNoeudParentEntier(ArbreEntier * fils, char dirrection);
ArbreEntier * creerArbreEntierVide(int valeur);

ArbreSymbole * creerArbreSymboleVide(char valeur);

