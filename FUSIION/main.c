#include "compression.h"
#include "decompression.h"
#include "lectureEcriture.h"
#include "sdata.h"


/*void main()
{
	freopen("stdout.txt", "w", stdout);
	freopen("stderr.txt", "w", stdout);

	donnees * d = malloc(sizeof(donnees));
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
}*/