#include <stdio.h>
#include <stdlib.h>
#include "sdata.h"
#include "compression.h"


//Initialise la structure donnée en paramètre
void initTableau(TabHuff* t) {
	int i;
	for (i = 0; i<256; i++) {
		t->Symbole[i] = 0;
		t->Occurrence[i] = 0;
		t->TailleS[i] = 0;
	}
	t->Taille = 0;
}

//Complète la structure de tableaux d'après un arbre de symboles
void ecritTableau(ArbreSymbole* a, TabHuff* t, unsigned char Longueur, unsigned char Symbole, unsigned char Indice) {
	unsigned char NewSymbole;

	if (estFeuille(a)) {
		t->Symbole[ioc(Indice)] = Symbole;
		t->Occurrence[ioc(Indice)] = a->occurrence;
		t->Taille++;
	}

	else {
		NewSymbole = Symbole + Longueur;
		ecritTableau(a->filsGauche, t, Longueur / 2, Symbole, Indice);
		ecritTableau(a->filsDroit, t, Longueur / 2, NewSymbole, Indice + Longueur);
	}
}

//Tri la structure selon un tri par insertion puis élimine les occurrences nulles de symbole
void TriArbreTableau(ArbreSymbole* a, TabHuff* t) {
	int i, j, x, y;

	initTableau(t);
	ecritTableau(a, t, 128, 0, 0);

	for (j = 1; j<t->Taille; j++) {
		x = t->Symbole[j];
		y = t->Occurrence[j];
		i = j - 1;

		while (i >= 0 && t->Occurrence[i] > y) {
			t->Symbole[i + 1] = t->Symbole[i];
			t->Occurrence[i + 1] = t->Occurrence[i];
			i--;
		}
		t->Symbole[i + 1] = x;
		t->Occurrence[i + 1] = y;
	}
	i = 0;

	while (t->Taille != 0 && t->Occurrence[0] == 0) {
		for (j = 0; j<t->Taille; j++) {
			t->Symbole[j] = t->Symbole[j + 1];
			t->Occurrence[j] = t->Occurrence[j + 1];
		}
		t->Taille--;
	}
}

//Renvoie 1 si une compression par Package Merge est nécessaire
int TestMerge(TabHuff* TH, donnees d) {
	int LmaxOpti = 0, i;
	for(i=0;i<TH->Taille;i++)
		if(TH->TailleS[i]>LmaxOpti)
			LmaxOpti=TH->TailleS[i];
	if (LmaxOpti <= d.Lmax)
		return 0;
	return 1;
}


void SymboleHuffman(ArbreSymbole* a, HuffSymb * HS, unsigned char Valeur) {

	if (estFeuille(a)) {
		HS->S[HS->Taille] = a->valeur;
		HS->H[HS->Taille] = Valeur;
		HS->T[HS->Taille] = a->taille;
		HS->Taille++;
	}
	else {
		if (a->filsGauche != NULL)
			SymboleHuffman(a->filsGauche, HS, Valeur * 2);
		if (a->filsDroit != NULL)
			SymboleHuffman(a->filsDroit, HS, Valeur * 2 + 1);
	}
}

void RemplitArbreHuffman(ArbreEntier* a, unsigned char symboleOrigine, int symboleHuffman, unsigned char Taille) {
	
	ArbreEntier * noeudCourant;
	char bit, MASK = 0x1;
	int bitCourant;
	noeudCourant = a;

	for (bitCourant = 7; bitCourant >= 0; bitCourant--)
	{
		bit = ((MASK << bitCourant)&symboleOrigine) >> bitCourant;
		if (bit == 0x1)
		{
			if (noeudCourant->filsDroit != NULL)
			{
				noeudCourant = noeudCourant->filsDroit;
			}
		}
		if (bit == 0x0) {
			if (noeudCourant->filsGauche != NULL)
			{
				noeudCourant = noeudCourant->filsGauche;
			}
		}
	}
	if (estFeuilleEntier(noeudCourant)) {
		noeudCourant->valeur = symboleHuffman;
		noeudCourant->taille = Taille;
	}
	else
	{
		printf("compression.c : transcoderASCII erreur\n"); exit(0);
	}
}

ArbreEntier* ConversionArbre(ArbreSymbole * a) {
	ArbreEntier* aa;
	HuffSymb HS;
	int i;
	for (i = 0; i<256; i++) {
		HS.H[i] = 0;
		HS.S[i] = 0;
		HS.T[i] = 0;
	}
	HS.Taille = 0;

	SymboleHuffman(a, &HS, 0);

	aa = creerArbreEntierVide(0,0);
	creerArbreBinaireEntier(8, aa);

	for (i = 0; i<HS.Taille; i++) {
		RemplitArbreHuffman(aa, HS.S[i], HS.H[i], HS.T[i]);
	}

	return aa;
}

void AjoutTailleTH(unsigned char Symbole, TabHuff* TH, int Taille) {
	int i = TH->Taille;
	while (i >= 0 && TH->Symbole[i] != 0)
		i--;
	while (i >= 0 && TH->Symbole[i] != Symbole)
		i--;
	TH->TailleS[i] = Taille;
}


void TailleSymbole(ArbreSymbole* a, int Taille, TabHuff* TH) {
	if (estFeuille(a)) {
		a->taille = Taille;
		AjoutTailleTH(a->valeur, TH, Taille);
	}
	else {
		Taille++;
		if (a->filsGauche != NULL)
			TailleSymbole(a->filsGauche, Taille, TH);
		if (a->filsDroit != NULL)
			TailleSymbole(a->filsDroit, Taille, TH);
	}
}

//Codage de Huffman
ArbreEntier* Huffman(donnees d, TabHuff* Tab) {
	int i = 0, j;
	TabArb Arb;

	//Définition d'un tableau d'arbres feuilles contenant les symboles et les occurrences associées
	for (j = 0; j<Tab->Taille; j++)
		Arb.a[j] = creerArbreSymboleVide(Tab->Symbole[j], Tab->Occurrence[j]);
	Arb.Taille = Tab->Taille;

	//Algorithme de Huffman, construction de l'arbre par le bas
	while (Arb.Taille>2) {
		//Assemblage des deux premières branches dans le premier arbre
		Arb.a[0] = ajout2ArbresS(Arb.a[0], Arb.a[1]);

		//Réduction de l'arbre en supprimant le membre de droite (inutile à présent)
		for (j = 1; j<Arb.Taille; j++)
			Arb.a[j] = Arb.a[j + 1];
		Arb.Taille--;

		//On fait de même pour toutes les branches suivantes selon leur occurrences
		//Pour savoir s'il faut mettre les noeuds à la même profondeur ou pas
		i = 1;
		while (i<Arb.Taille-1 && (Arb.a[0]->occurrence >= Arb.a[i]->occurrence + Arb.a[i + 1]->occurrence)) {
			Arb.a[i] = ajout2ArbresS(Arb.a[i], Arb.a[i + 1]);
			i++;
			for (j = i; j<Arb.Taille; j++)
				Arb.a[j] = Arb.a[j+1];
			Arb.Taille--;
		}
	}
	//Rentre dans le if dans tous les cas (vérification au cas où il n'y ait eu aucun symbole à coder)
	if(Arb.Taille!=0){
		//S'il reste un seul arbre, c'est qu'il n'y a qu'un seul symbole à coder, sinon, il faut ajouter les deux restants
		if(Arb.Taille==2)
			Arb.a[0] = ajout2ArbresS(Arb.a[0], Arb.a[1]);
		//On complète la structure TabHuff avec l'arbre créé
		TailleSymbole(Arb.a[0], 0, Tab);
		//print_Abr(AS, 0);
		return ConversionArbre(Arb.a[0]);
	}
	//Ne devrait jamais arriver
	exit(0);
}

void InitPM(TabMerge* TM, TabHuff* TH) {
	int i;
	for (i = 0; i<2048; i++) {
		liste* lp = malloc(sizeof(liste*));
		liste* lm = malloc(sizeof(liste*));
		TM->Package[i] = lp;
		TM->Package[i]->valeur = 0;
		TM->Package[i]->Suivant = NULL;
		TM->Merge[i] = lm;
		TM->Merge[i]->valeur = 0;
		TM->Merge[i]->Suivant = NULL;

		TM->PoidsP[i] = 0;
		TM->PoidsM[i] = 0;
	}
	for(i=0;i<TH->Taille;i++)
		TM->Occurrence2[i]=0;
	TM->TailleP = 0;
	TM->TailleM = 0;
}

liste* Concat2Listes(liste* L1, liste* L2) {
	liste* L3;
	L3 = L1;
	if (L3 == NULL)
		return L2;
	while (L3->Suivant != NULL)
		L3 = L3->Suivant;
	L3->Suivant = L2;
	L3 = L1;
	return L3;
}

void MergeAjout(TabHuff* TH, TabMerge* TM) {
	int i = 0, j = 0, k;
	TM->TailleM = TM->TailleP + TH->Taille;
	for(k=0; k<TM->TailleM; k++){
		TM->Merge[k]->Suivant=NULL;
		TM->Merge[k]->valeur=0;
		TM->PoidsM[k]=0;
	}
	for (k = 0; k<TM->TailleM; k++) {
		if (i<TH->Taille && TH->Occurrence[i]<=TM->PoidsP[j]) {
			TM->Merge[k]->valeur = TH->Symbole[i];
			TM->PoidsM[k] = TH->Occurrence[i];
			i++;
		}
		else if(j<TM->TailleP){
			TM->Merge[k] = TM->Package[j];
			TM->PoidsM[k] = TM->PoidsP[j];
			j++;
		}
	}
}

void AjoutSymbole(unsigned char Symbole, TabHuff* TH, TabMerge* TM) {
	int i = 0;
	while (i<TH->Taille && TH->Symbole[i] != Symbole)
		i++;
	if (i != TH->Taille)
		TM->Occurrence2[i]++;
}

ArbreSymbole* ConstruireArbre(TabHuff* TH, TabMerge* TM, int Prof, int Indice) {
	if (Prof == TM->Occurrence2[Indice]){
		return creerArbreSymboleVide(TH->Symbole[Indice],0);
	}
	return ajout2ArbresS(ConstruireArbre(TH, TM, Prof + 1, Indice / 2), ConstruireArbre(TH, TM, Prof + 1, Indice + Indice / 2));

}

ArbreSymbole* ArbreMerge(TabHuff* TH, TabMerge* TM) {
	return ConstruireArbre(TH, TM, 0, TH->Taille / 2);
}

ArbreEntier* Merge(donnees d, TabHuff* TH) {
	TabMerge* TM = malloc(sizeof(TabMerge));
	liste* L;
	int i, k;

	InitPM(TM, TH);

	for (k = 0; k<d.Lmax; k++) {

		MergeAjout(TH, TM);

		i = 0;
		TM->TailleP = 0;
		while (i<TM->TailleM - 1) {
			TM->Package[TM->TailleP] = Concat2Listes(TM->Merge[i], TM->Merge[i + 1]);
			TM->PoidsP[TM->TailleP] = TM->PoidsM[i] + TM->PoidsM[i + 1];
			TM->TailleP++;
			i += 2;
		}
		if(i!=TM->TailleM){
			TM->Package[TM->TailleP] = TM->Merge[i];
			TM->PoidsP[TM->TailleP] = TM->PoidsM[i];
			TM->TailleP++;			
		}

	}
	//Ne devrait jamais arriver
	if (TM->TailleP != (TH->Taille - 2))
		exit(0);

	for (k = 0; k<TM->TailleP; k++) {
		L = TM->Package[k];
		while (L != NULL) {
			AjoutSymbole(L->valeur, TH, TM);
			L = L->Suivant;
		}
	}
	for(k=0;k<TH->Taille;k++)
		//printf("%d\n", TM.Occurrence2[k]);


	return ConversionArbre(ArbreMerge(TH, TM));
}

void RealCanonique(Canonique* C, TabHuff* TH){
	int i;
	C->Taille=TH->Taille;
	for(i=0;i<C->Taille;C++){
		C->Symbole[i]=TH->Symbole[i];
		C->TailleS[i]=TH->TailleS[i];
	}
}

ArbreEntier * Compression(donnees d, Canonique* C){
	ArbreEntier* a;
	TabHuff* Tab = malloc(sizeof(TabHuff));

	TriArbreTableau(d.arbre, Tab);

	a = Huffman(d, Tab);

	//if(TestMerge(&Tab,d))
		//a = Merge(d, Tab);

	RealCanonique(C, Tab);

	return a;
}


