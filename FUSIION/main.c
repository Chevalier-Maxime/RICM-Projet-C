#include "compression.h"
#include "decompression.h"
#include "lectureEcriture.h"
#include "entete.h"
#include "desentetage.h"
#include "sdata.h"
#include "pretraitement.h"
#include "depretraitage.h"
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
		fichierTemporaire = fopen(NOM_FICHIER_TEMP, "w+b");
		pretraiter(fichierACompresser, fichierTemporaire);
		fclose(fichierACompresser);
		//Rempli la structure d a partir du fichier. ----> Si pretraitement mettre fichier temporaire ici
		rewind(fichierTemporaire);
		remplirDonneeFichierASCII(d, fichierTemporaire);

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
		rewind(fichierTemporaire);
		//On ecrit l'entete dans le fichier Compressé
		ecrireentete(e, fichierCompresse);
		//Puis on réalise la compression
		realiserCompressionASCII(a, d, e, fichierTemporaire, fichierCompresse);

		fclose(fichierTemporaire);
		fclose(fichierCompresse);

		printf("La compression est terminée.\n"); exit(0);

	}
	else if (decompression == 2)
	{
		//decompresser


		//TEST BONNE OUVERTURE
		dejaPasse = 0;
		do
		{
			if (dejaPasse) printf("Impossible d'ouvrir ce fichier...\n");
			printf("Quel fichier decompresser ? ");
			scanf("%s", &nomFichierCompresser);
			fichierCompresse = fopen(nomFichierCompresser, "r+b");
			dejaPasse = 1;
		} while (fichierCompresse==NULL);

		printf("Sous quel nom decompresser votre fichier ? ");
		scanf("%s", &nomFichierDecompresser);
		fichierTemporaire = fopen(NOM_FICHIER_TEMP, "w+b"); // ----Si depretraitement changer ici en fichier temp et dans la suite aussi


		//Desenteter
		entete * e = decrypterentete(fichierCompresse);

		//Creation de l'arbre canonique
		ArbreSymbole * arbreCanonique = Decompression(e->Symbole, e->TailleS, e->nbSymbolesDifferents);
		//print_Abr(arbreCanonique, 0);

		realiserDecompressionASCII(arbreCanonique, e, fichierCompresse, fichierTemporaire);
		fclose(fichierCompresse);
		
		//faire depretraitement
		fclose(fichierTemporaire);
		fichierTemporaire = fopen(NOM_FICHIER_TEMP, "r+b");
		fichierDecompresse = fopen(nomFichierDecompresser, "w+b");

		depretraiter(fichierTemporaire, fichierDecompresse);

		fclose(fichierDecompresse);
		fclose(fichierTemporaire);
		printf("Decompression terminée :)\n");
	}
}