#include "compression.h"
#include "decompression.h"
#include "lectureEcriture.h"
#include "entete.h"
#include "desentetage.h"
#include "sdata.h"
#include <stdio.h>
#include <stdlib.h>
// Manque les include des pretraitements


void main()
{
	//début du main
	int tauxCompression;
	int decompression = 0;
	int dejaPasse = 0;
	int retester = 0;
	do {
		if (dejaPasse)
		{
			fprintf(stderr, "");
			printf("Veuillez tapez un des choix entre parenthèses. Reessayer ? (1 = oui, 0 = non) ->  ");
			scanf("%d", &retester);
			if (!retester)
			{
				exit(0);
			}
		}
		printf("Voulez-vous compresser(1) ou decompresser(2) ? ");
		scanf("%d", &decompression);
		dejaPasse = 1;
	} while (decompression<1 || decompression>3);

	if (decompression == 1)
	{
		//compresser
		printf("Quel est le taux de compression souhaité ? ");
		scanf("%d",&tauxCompression); //--------------------------------Demander a Hugo quoi faire avec

		printf("Sous quel nom voulez vous enregister votre fichier ? ");
		scanf("%s", &nomFichierCompresser);



		donnees * d = malloc(sizeof(donnees));
		TabHuff * tableauHuffman = malloc(sizeof(TabHuff));
		d->Lmax = 8;
		d->nbSymboles = 0;
		d->arbre = creerArbreSymboleVide(0, 0);
		creerArbreBinaire(8, d->arbre);

		//Ouverture du fichierACompresser
		lireFichier(d);
		//Pretraitement ...

		//Rempli la structure d a partir du fichier. ----> Si pretraitement mettre fichier temporaire ici
		remplirDonneeFichierASCII(d, fichierACompresser);

		ArbreEntier * a = Compression(*d, tableauHuffman);
		//print_Abr(a, 0);

		entete * e = malloc(sizeof(entete));
		e->nbSymboles = d->nbSymboles;
		e->nbSymbolesDifferents = tableauHuffman->Taille;
		int i;
		for (i = 0; i < 256; i++)
		{
			e->Symbole[i] = tableauHuffman->Symbole[i];
			e->TailleS[i] = tableauHuffman->TailleS[i];
		}

		fichierCompresse = fopen(nomFichierCompresser, "w+b");
		rewind(fichierACompresser);
		//On ecrit l'entete dans le fichier Compressé
		ecrireentete(e, fichierCompresse);
		//Puis on réalise la compression
		realiserCompressionASCII(a, d, e, fichierACompresser, fichierCompresse);

		printf("La compression est terminée.\n"); exit(0);

	}
	else if (decompression == 2)
	{
		//decompresser
		printf("Quel fichier decompresser ? ");
		scanf("%s", &nomFichierCompresser);

		printf("Sous quel nom decompresser votre fichier ? ");
		scanf("%s", &nomFichierDecompresser);

		//--------------------------------------------------------------------------AJOUTER TEST BONNE OUVERTURE
		fichierCompresse = fopen(nomFichierCompresser, "r+b");
		fichierDecompresse = fopen(nomFichierDecompresser, "w+b"); // ----Si depretraitement changer ici en fichier temp

		//Desenteter
		entete * e = decrypterentete(fichierCompresse);

		//Creation de l'arbre canonique
		ArbreSymbole * arbreCanonique = Decompression(e->Symbole, e->TailleS, e->nbSymbolesDifferents);
		printf("\n\n\n");
		//print_Abr(arbreCanonique, 0);

		realiserDecompressionASCII(arbreCanonique, e, fichierCompresse, fichierDecompresse);

		fclose(fichierDecompresse);
		fclose(fichierCompresse);

		printf("Decompression terminée :)\n");
		//faire depretraitement
		// ...

	}


	/*donnees * d = malloc(sizeof(donnees));
	TabHuff * tableauHuffman = malloc(sizeof(TabHuff));
	d->Lmax = 8;
	d->nbSymboles = 0;
	d->arbre = creerArbreSymboleVide(0, 0);
	//Met des 1 dans les noeuds, mettre des 0 --> demander HUGO
	creerArbreBinaire(8, d->arbre);
	lireFichier(d);
	ArbreEntier * a = Compression(*d, tableauHuffman);
	//print_Abr(a, 0);

	entete * e = malloc(sizeof(entete));
	e->nbSymboles = d->nbSymboles;
	int i;
	for (i = 0; i < 256; i++)
	{
		e->Symbole[i] = tableauHuffman->Symbole[i];
		e->TailleS[i] = tableauHuffman->TailleS[i];
	}

	int padding = realiserCompressionASCII(a, d, e);

	fclose(fichierCompresse);
	fclose(fichierACompresser);

	fichierCompresse = fopen(NOM_FICHIER_COMP, "r+b");
	fichierADecompresser = fopen("licorne.txt", "w+b");

	ArbreSymbole * arbreCanonique = Decompression(tableauHuffman->Symbole, tableauHuffman->TailleS, d->nbSymboles);
	printf("\n\n\n");
	print_Abr(arbreCanonique, 0);

	realiserDecompressionASCII(arbreCanonique, d, e);

	fclose(fichierADecompresser);
	fclose(fichierCompresse);
	*/
}