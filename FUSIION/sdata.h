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



typedef struct entete //MODIFICATION TAB A METTRE ICI ET PAS DANS DONNEE
{
	int nbSymboles;
	int nbSymbolesDifferents;
	int nbPadding;
	int tailleEntete;
	int TailleS[256];
	unsigned char Symbole[256];
} entete;

union octet{
	char symbole;
	//#TODO a voir...
};


//Retourne la puissance de 2 du paramètre
int Puis2(int Valeur);
//Fonction int_of_char qui renvoie l'entier associé à un unsigned char
int ioc(unsigned char c);

//Réalise un malloc sur une structure d'arbre (une feuille) et complète avec le symbole et l'occurrence associé
ArbreEntier * creerArbreEntierVide(int valeur, int occurrence);
ArbreSymbole * creerArbreSymboleVide(char valeur, int occurrence);

//Créé un arbre binaire équilibré d'une hauteur donné à partir d'une feuille
void creerArbreBinaire(int hauteur, ArbreSymbole * arbre);
void creerArbreBinaireEntier(int hauteur, ArbreEntier * arbre);

int nombreOccurrence(ArbreEntier * arbre, unsigned char symbole);
void ajouterOccurenceAbreSymbole(ArbreSymbole * a, char * symbole);

//Renvoie 1 si l'arbre donné est une feuille, 0 sinon
int estFeuille(ArbreSymbole * arbre);
int estFeuilleEntier(ArbreEntier * arbre);


ArbreEntier * ajouterNoeudParentEntier(ArbreEntier * fils, char dirrection);

//Renvoie un arbre dont le fils gauche est a et le fils droit a2
ArbreSymbole * ajout2ArbresS(ArbreSymbole * a, ArbreSymbole * a2);

//Ecrit l'arbre sur le terminal
void print_Abr(ArbreSymbole* a, int l);
void print_AbrE(ArbreEntier* a, int l);

entete * creerEntete(int nbSymb, int nbSymbDifferents, int tabI[256], unsigned char tabS[256]);

#endif // SDATA_H
